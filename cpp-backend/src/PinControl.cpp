#include "PinControl.hpp"

#include <stdio.h>

#include <libserial/SerialPort.h>

#include <chrono>

LibSerial::SerialPort g_serial_port;

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
    g_serial_port.Open(port);
    g_serial_port.SetBaudRate(LibSerial::BaudRate::BAUD_9600);
    g_serial_port.SetCharacterSize(LibSerial::CharacterSize::CHAR_SIZE_8);
    g_serial_port.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);
    g_serial_port.SetParity(LibSerial::Parity::PARITY_NONE);
    g_serial_port.SetStopBits(LibSerial::StopBits::STOP_BITS_DEFAULT);

    bool arduino_ready = false;

    // 10 attempts with a 1 second timeout each
    for (uint64_t i = 0; i < 10; i++) {
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        g_serial_port.WriteByte((char)ARDUINO_COMMAND_INIT);
        bool success = false;
        while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start).count() < 1) {
            if (g_serial_port.IsDataAvailable()) {
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
        g_serial_port.Close();
        exit(1);
    }

    at_quick_exit(StopSerial); // ensure it is called to close the serial port

    uint8_t c;
    g_serial_port.ReadByte(c);
    if (c != ARDUINO_RESPONSE_INIT) {
        printf("Invalid response from Arduino\n");
        g_serial_port.Close();
        exit(1);
    }
}

void StopSerial() {
    if (g_serial_port.IsOpen())
        g_serial_port.Close();
}

void ArduinoSendByte(uint8_t byte) {
    g_serial_port.WriteByte(byte);
    uint8_t c;
    g_serial_port.ReadByte(c);
    if (c != ARDUINO_RESPONSE_ACK) {
        printf("Invalid response from Arduino\n");
        g_serial_port.Close();
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
    printf("Writing to pin %d: %s\n", pin, value ? "HIGH" : "LOW");
    ArduinoSendByte(ARDUINO_COMMAND_WRITE);
    ArduinoSendByte(pin & 0xFF);
    ArduinoSendByte(value);
    uint8_t c;
    g_serial_port.ReadByte(c);
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
    printf("Reading from pin %d\n", pin);
    ArduinoSendByte(ARDUINO_COMMAND_READ);
    ArduinoSendByte(pin & 0xFF);
    uint8_t c;
    g_serial_port.ReadByte(c);
    if (c == ARDUINO_RESPONSE_SUCCESS) {
        g_serial_port.ReadByte(c);
        printf("Received: %d\n", c);
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
    printf("Configuring pin %d to %s\n", pin, mode ? "OUTPUT" : "INPUT");
    ArduinoSendByte(ARDUINO_COMMAND_CONFIG);
    ArduinoSendByte(pin & 0xFF);
    ArduinoSendByte(mode);
    uint8_t c;
    g_serial_port.ReadByte(c);
    if (c != ARDUINO_RESPONSE_SUCCESS)
        printf("Error configuring pin\n");
}