#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>

#include <unistd.h>

#include <sys/wait.h>

#include <cjson/cJSON.h>

#include <libserial/SerialPort.h>

#include "PinControl.hpp"
#include "CommandParser.hpp"

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
            ParseCommand(received_json, pipe_fd_w[1]);
            cJSON_Delete(received_json);
        } while (n > 0);
        while (waitpid(pid, NULL, 0) == -1);

        close(pipe_fd_r[0]);
        close(pipe_fd_w[1]);
    }

    return 0;
}