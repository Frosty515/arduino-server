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
#include "ServerInternal.hpp"

#include <string>
#include <string_view>

#include <stdio.h>
#include <string.h>

#include <cjson/cJSON.h>

void WritePin(int pin, bool value) {
    cJSON* request = cJSON_CreateObject();
    cJSON_AddStringToObject(request, "type", "response");
    cJSON_AddStringToObject(request, "command", "set-pin-state");
    cJSON_AddNumberToObject(request, "pin", pin);
    cJSON_AddBoolToObject(request, "value", value);
    char* request_str = cJSON_PrintBuffered(request, 256, 0);

    std::string_view data(request_str);

    cJSON_Delete(request);
    std::string response_str = Server::SendHTTPPostRequest("/api/set-pin-state", data);

    cJSON* response_json = cJSON_Parse(response_str.c_str());
    cJSON* status = cJSON_GetObjectItemCaseSensitive(response_json, "status");
    if (cJSON_IsString(status) && status->valuestring != NULL) {
        if (strcmp(status->valuestring, "ok") != 0) {
            printf("Error: %s\n", response_str.c_str());
        }
    }
    cJSON_Delete(response_json);
}

bool ReadPin(int pin) {
    cJSON* request = cJSON_CreateObject();
    cJSON_AddStringToObject(request, "type", "response");
    cJSON_AddStringToObject(request, "command", "get-pin-state");
    cJSON_AddNumberToObject(request, "pin", pin);
    char* request_str = cJSON_PrintBuffered(request, 256, 0);

    std::string_view data(request_str);

    cJSON_Delete(request);

    std::string response_str = Server::SendHTTPPostRequest("/api/get-pin-state", data);
    cJSON* response_json = cJSON_Parse(response_str.c_str());
    cJSON* value = cJSON_GetObjectItemCaseSensitive(response_json, "value");
    bool result = false;
    if (cJSON_IsBool(value) || cJSON_IsNumber(value))
        result = value->valueint;
    else if (cJSON_IsString(value))
        result = strcmp(value->valuestring, "true") == 0;
    else {
        printf("Error: %s\n", response_str.c_str());
    }
    cJSON_Delete(response_json);
    return result;
}

void ConfigPinMode(int pin, bool mode) {
    cJSON* request = cJSON_CreateObject();
    cJSON_AddStringToObject(request, "type", "response");
    cJSON_AddStringToObject(request, "command", "config-pin-mode");
    cJSON_AddNumberToObject(request, "pin", pin);
    cJSON_AddBoolToObject(request, "mode", mode);
    char* request_str = cJSON_PrintBuffered(request, 256, 0);

    std::string_view data(request_str);

    cJSON_Delete(request);

    std::string response_str = Server::SendHTTPPostRequest("/api/config-pin-mode", data);
    cJSON* response_json = cJSON_Parse(response_str.c_str());

    cJSON* status = cJSON_GetObjectItemCaseSensitive(response_json, "status");
    if (cJSON_IsString(status) && status->valuestring != NULL) {
        if (strcmp(status->valuestring, "ok") != 0) {
            printf("Error: %s\n", response_str.c_str());
        }
    }
    cJSON_Delete(response_json);
}
