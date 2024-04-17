#ifndef _COMMAND_PARSER_HPP
#define _COMMAND_PARSER_HPP

#include <cjson/cJSON.h>

void ParseCommand(cJSON* command_json, int out_fd);

#endif /* _COMMAND_PARSER_HPP */