/*
Copyright (©) 2024  Frosty515

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "PinControl.hpp"

#include <signal.h>
#include <stdio.h>
#include <string.h>

#include <libserialport.h>

#include <chrono>

sp_port* g_serial_port;
sp_port_config* g_serial_port_config;

enum ArduinoCommand {
    ARDUINO_COMMAND_INIT = 0xFF,
    ARDUINO_COMMAND_WRITE = 0,
    ARDUINO_COMMAND_READ = 1,
    ARDUINO_COMMAND_CONFIG = 2
};

enum ArduinoResponse {
    ARDUINO_RESPONSE_INIT = 0xFF,
    ARDUINO_RESPONSE_SUCCESS = 0,
    ARDUINO_RESPONSE_ERROR = 1,
    ARDUINO_RESPONSE_ACK = 2
};

void StartSerial(const char* port) {
    sp_return rc = sp_get_port_by_name(port, &g_serial_port);
    if (rc != SP_OK) {
        printf("Error getting port by name\n");
        exit(1);
    }
    rc = sp_open(g_serial_port, SP_MODE_READ_WRITE);
    if (rc != SP_OK) {
        printf("Error opening port\n");
        exit(1);
    }

    sp_new_config(&g_serial_port_config);
    sp_set_config_baudrate(g_serial_port_config, 9600);
    sp_set_config_bits(g_serial_port_config, 8);
    sp_set_config_parity(g_serial_port_config, SP_PARITY_NONE);
    sp_set_config_stopbits(g_serial_port_config, 1);

    rc = sp_set_config(g_serial_port, g_serial_port_config);
    if (rc != SP_OK) {
        printf("Error setting port config\n");
        exit(1);
    }

    bool arduino_ready = false;

    // 10 attempts with a 1 second timeout each
    for (uint64_t i = 0; i < 10; i++) {
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        uint8_t byte = ARDUINO_COMMAND_INIT;
        sp_blocking_write(g_serial_port, &byte, 1, 1000);
        bool success = false;
        while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start).count() < 1) {
            if (sp_input_waiting(g_serial_port) > 0) {
                success = true;
                break;
            }
        }
        if (success) {
            printf("Attempt %lu: Arduino ready\n", i + 1);
            arduino_ready = true;
            break;
        }
    }
    if (!arduino_ready) {
        printf("Arduino not ready\n");
        StopSerial();
        exit(1);
    }

    at_quick_exit(StopSerial); // ensure it is called to close the serial port

    {
        struct sigaction sa;
        memset(&sa, 0, sizeof(sa));
        sa.sa_handler = [](int) -> void {
            StopSerial();
            exit(0);
        };
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGTERM, &sa, NULL);
        sigaction(SIGSTOP, &sa, NULL);
    }

    uint8_t c;
    rc = sp_blocking_read(g_serial_port, &c, 1, 1000);
    if (rc < 0 || c != ARDUINO_RESPONSE_INIT) {
        printf("Invalid response from Arduino\n");
        StopSerial();
        exit(1);
    }
}

void StopSerial() {
    sp_close(g_serial_port);
    sp_free_port(g_serial_port);
    sp_free_config(g_serial_port_config);
}

void ArduinoSendByte(uint8_t byte) {
    sp_blocking_write(g_serial_port, &byte, 1, 1000);
    uint8_t c = 0xFF;
    sp_return rc = sp_blocking_read(g_serial_port, &c, 1, 1000);
    if (rc < 0 || c != ARDUINO_RESPONSE_ACK) {
        printf("Invalid response from Arduino\n");
        StopSerial();
        exit(1);
    }
}

/*
Write command layout:
    1 byte: command
    1 byte: pin
    1 byte: value

    we wait for an ACK from the Arduino after each byte
*/

void WritePin(int pin, bool value) {
    if (pin == 1 || pin == 0) {
        printf("Cannot write to pin %d. It is reserved for serial communication.\n", pin);
        return;
    }
    // printf("Writing to pin %d: %s\n", pin, value ? "HIGH" : "LOW");
    ArduinoSendByte(ARDUINO_COMMAND_WRITE);
    ArduinoSendByte(pin & 0xFF);
    ArduinoSendByte(value);
    uint8_t c = 0xFF;
    sp_blocking_read(g_serial_port, &c, 1, 1000);
    if (c != ARDUINO_RESPONSE_SUCCESS)
        printf("Error writing pin\n");
}

/*
Read command layout:
    1 byte: command
    1 byte: pin

    we wait for an ACK from the Arduino after each byte

    the Arduino will respond with the value of the pin
*/

bool ReadPin(int pin) {
    if (pin == 1 || pin == 0) {
        printf("Cannot read from pin %d. It is reserved for serial communication.\n", pin);
        return false;
    }
    // printf("Reading from pin %d\n", pin);
    ArduinoSendByte(ARDUINO_COMMAND_READ);
    ArduinoSendByte(pin & 0xFF);
    uint8_t c = 0xFF;
    sp_blocking_read(g_serial_port, &c, 1, 1000);
    if (c == ARDUINO_RESPONSE_SUCCESS) {
        c = 0xFF;
        sp_blocking_read(g_serial_port, &c, 1, 1000);
        // printf("Received: %d\n", c);
        return c;
    }
    else
        printf("Error reading pin\n"); 
    return false;
}

/*
Config command layout:
    1 byte: command
    1 byte: pin
    1 byte: mode

    we wait for an ACK from the Arduino after each byte
*/

void ConfigPinMode(int pin, bool mode) {
    // printf("Configuring pin %d to %s\n", pin, mode ? "OUTPUT" : "INPUT");
    ArduinoSendByte(ARDUINO_COMMAND_CONFIG);
    ArduinoSendByte(pin & 0xFF);
    ArduinoSendByte(mode);
    uint8_t c = 0xFF;
    sp_blocking_read(g_serial_port, &c, 1, 1000);
    if (c != ARDUINO_RESPONSE_SUCCESS)
        printf("Error configuring pin\n");
}