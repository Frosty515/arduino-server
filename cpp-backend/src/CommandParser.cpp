#include "CommandParser.hpp"
#include "PinControl.hpp"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void ParseCommand(cJSON* command_json, int out_fd) {
    cJSON* type = cJSON_GetObjectItemCaseSensitive(command_json, "type");
    if (cJSON_IsString(type) && type->valuestring != NULL) {
        if (strcmp(type->valuestring, "message") == 0) {
            cJSON* msg = cJSON_GetObjectItemCaseSensitive(command_json, "msg");
            if (cJSON_IsString(msg) && (msg->valuestring != NULL))
                printf("Received: %s\n", msg->valuestring);
            else
                printf("Received: %s\n", cJSON_Print(command_json));
        }
        else if (strcmp(type->valuestring, "command") == 0) {
            cJSON* command = cJSON_GetObjectItemCaseSensitive(command_json, "command");
            if (cJSON_IsString(command) && (command->valuestring != NULL)) {
                if (strcmp(command->valuestring, "set-pin-state") == 0) {
                    cJSON* pin = cJSON_GetObjectItemCaseSensitive(command_json, "pin");
                    cJSON* value = cJSON_GetObjectItemCaseSensitive(command_json, "value");
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
                    write(out_fd, response_str, len);
                    delete[] response_str;
                    cJSON_Delete(response);
                }
                else if (strcmp(command->valuestring, "get-pin-state") == 0) {
                    cJSON* pin = cJSON_GetObjectItemCaseSensitive(command_json, "pin");
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
                    write(out_fd, response_str, len);
                    delete[] response_str;
                    cJSON_Delete(response);
                }
                else if (strcmp(command->valuestring, "config-pin-mode") == 0) {
                    cJSON* pin = cJSON_GetObjectItemCaseSensitive(command_json, "pin");
                    cJSON* mode = cJSON_GetObjectItemCaseSensitive(command_json, "mode");
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
                    write(out_fd, response_str, len);
                    delete[] response_str;
                    cJSON_Delete(response);
                }
            }
        }
    }
    else
        printf("Received: %s\n", cJSON_Print(command_json));
}