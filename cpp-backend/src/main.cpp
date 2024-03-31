#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>

#include <unistd.h>

#include <sys/wait.h>

#include <cjson/cJSON.h>

#include <libserial/SerialPort.h>

#include "PinControl.hpp"

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s <script_path> <serial_port>\n", argv[0]);
        return 1;
    }

    // we need to format the string into a path. It will be in "node <script_path>" format.
    std::string command = "node ";
    command += argv[1];

    int pipe_fd_r[2];
    if (pipe(pipe_fd_r) == -1) {
        perror("pipe_r");
        return 1;
    }

    int pipe_fd_w[2];
    if (pipe(pipe_fd_w) == -1) {
        perror("pipe_w");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // child process
        close(pipe_fd_w[1]);
        close(pipe_fd_r[0]);

        dup2(pipe_fd_w[0], STDIN_FILENO);
        dup2(pipe_fd_r[1], STDOUT_FILENO);


        execlp("node", "node", argv[1], NULL);
    } else {
        // parent process
        close(pipe_fd_w[0]); // close for reading
        close(pipe_fd_r[1]); // close for writing

        StartSerial(argv[2]);

        // read data from the pipe
        int n;
        do {
            char buffer[1024];
            n = read(pipe_fd_r[0], buffer, sizeof(buffer) - 1);
            buffer[n] = '\0';
            cJSON* received_json = cJSON_Parse(buffer);
            if (received_json == NULL) {
                const char *error_ptr = cJSON_GetErrorPtr(); 
                if (error_ptr != NULL)
                    printf("Error: %s\n", error_ptr); 
                cJSON_Delete(received_json); 
                return 1;
            }
            cJSON* type = cJSON_GetObjectItemCaseSensitive(received_json, "type");
            if (cJSON_IsString(type) && type->valuestring != NULL) {
                if (strcmp(type->valuestring, "message") == 0) {
                    cJSON* msg = cJSON_GetObjectItemCaseSensitive(received_json, "msg");
                    if (cJSON_IsString(msg) && (msg->valuestring != NULL))
                        printf("Received: %s\n", msg->valuestring);
                    else
                        printf("Received: %s\n", cJSON_Print(received_json));
                }
                else if (strcmp(type->valuestring, "command") == 0) {
                    cJSON* command = cJSON_GetObjectItemCaseSensitive(received_json, "command");
                    if (cJSON_IsString(command) && (command->valuestring != NULL)) {
                        if (strcmp(command->valuestring, "set-pin-state") == 0) {
                            cJSON* pin = cJSON_GetObjectItemCaseSensitive(received_json, "pin");
                            cJSON* value = cJSON_GetObjectItemCaseSensitive(received_json, "value");
                            int pin_number = -1;
                            if (cJSON_IsNumber(pin))
                                pin_number = pin->valueint;
                            else if (cJSON_IsString(pin))
                                pin_number = atoi(pin->valuestring);
                            bool value_bool = false;
                            if (cJSON_IsBool(value) || cJSON_IsNumber(value))
                                value_bool = value->valueint;
                            else if (cJSON_IsString(value))
                                value_bool = strcmp(value->valuestring, "true") == 0;
                            WritePin(pin_number, value_bool);
                            cJSON* response = cJSON_CreateObject();
                            cJSON_AddStringToObject(response, "type", "response");
                            cJSON_AddStringToObject(response, "command", "set-pin-state");
                            cJSON_AddStringToObject(response, "status", "ok");
                            char* response_str = new char[1024];
                            cJSON_PrintPreallocated(response, response_str, 1023, 0);
                            printf("Sending: %s\n", response_str);
                            int len = strlen(response_str);
                            response_str[len] = '\n'; // add a newline character at the end
                            response_str[len + 1] = '\0'; // add a null character at the end
                            write(pipe_fd_w[1], response_str, len);
                            delete[] response_str;
                            cJSON_Delete(response);
                        }
                        else if (strcmp(command->valuestring, "get-pin-state") == 0) {
                            cJSON* pin = cJSON_GetObjectItemCaseSensitive(received_json, "pin");
                            int pin_number = -1;
                            if (cJSON_IsNumber(pin))
                                pin_number = pin->valueint;
                            else if (cJSON_IsString(pin))
                                pin_number = atoi(pin->valuestring);
                            bool value = ReadPin(pin_number);
                            cJSON* response = cJSON_CreateObject();
                            cJSON_AddStringToObject(response, "type", "response");
                            cJSON_AddStringToObject(response, "command", "get-pin-state");
                            cJSON_AddNumberToObject(response, "pin", pin_number);
                            cJSON_AddBoolToObject(response, "value", value);
                            char* response_str = new char[1024];
                            cJSON_PrintPreallocated(response, response_str, 1023, 0);
                            printf("Sending: %s\n", response_str);
                            int len = strlen(response_str);
                            response_str[len] = '\n'; // add a newline character at the end
                            response_str[len + 1] = '\0'; // add a null character at the end
                            write(pipe_fd_w[1], response_str, len);
                            delete[] response_str;
                            cJSON_Delete(response);
                        }
                        else if (strcmp(command->valuestring, "config-pin-mode") == 0) {
                            cJSON* pin = cJSON_GetObjectItemCaseSensitive(received_json, "pin");
                            cJSON* mode = cJSON_GetObjectItemCaseSensitive(received_json, "mode");
                            int pin_number = -1;
                            if (cJSON_IsNumber(pin))
                                pin_number = pin->valueint;
                            else if (cJSON_IsString(pin))
                                pin_number = atoi(pin->valuestring);
                            bool mode_bool = false;
                            if (cJSON_IsBool(mode) || cJSON_IsNumber(mode))
                                mode_bool = mode->valueint;
                            else if (cJSON_IsString(mode))
                                mode_bool = strcmp(mode->valuestring, "OUTPUT") == 0;
                            ConfigPinMode(pin_number, mode_bool);
                            cJSON* response = cJSON_CreateObject();
                            cJSON_AddStringToObject(response, "type", "response");
                            cJSON_AddStringToObject(response, "command", "config-pin-mode");
                            cJSON_AddStringToObject(response, "status", "ok");
                            char* response_str = new char[1024];
                            cJSON_PrintPreallocated(response, response_str, 1023, 0);
                            printf("Sending: %s\n", response_str);
                            int len = strlen(response_str);
                            response_str[len] = '\n'; // add a newline character at the end
                            response_str[len + 1] = '\0'; // add a null character at the end
                            write(pipe_fd_w[1], response_str, len);
                            delete[] response_str;
                            cJSON_Delete(response);
                        }
                    }
                }
            }
            else
                printf("Received: %s\n", cJSON_Print(received_json));
            cJSON_Delete(received_json);
        } while (n > 0);
        while (waitpid(pid, NULL, 0) == -1);

        close(pipe_fd_r[0]);
        close(pipe_fd_w[1]);
    }

    return 0;
}