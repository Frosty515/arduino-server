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

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>

#include <unistd.h>

#include <sys/wait.h>

#include <cjson/cJSON.h>

#include "PinControl.hpp"
#include "CommandParser.hpp"

pid_t g_childPID;

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
    }
    else {
        g_childPID = pid;

        at_quick_exit([]() -> void {
            kill(g_childPID, SIGTERM);
            sleep(1); // wait for the child to exit
            // kill(g_childPID, SIGKILL);
        });

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
            ParseCommand(received_json, pipe_fd_w[1]);
            cJSON_Delete(received_json);
        } while (n > 0);
        while (waitpid(pid, NULL, 0) == -1);

        close(pipe_fd_r[0]);
        close(pipe_fd_w[1]);
    }

    return 0;
}