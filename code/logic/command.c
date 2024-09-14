/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "fossil/lib/command.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include <sys/stat.h>

#ifdef _WIN32
    #include <windows.h>
    #define _FOSSIL_PATH_SEPARATOR ";"
#else
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #define _FOSSIL_PATH_SEPARATOR ":"
#endif

// Define a typedef for char* to make the code more readable
typedef char* fossil_command_t;

// Function to run a command
int32_t fossil_command(fossil_command_t process) {
    int32_t result = system(process);
    if (result == -1) {
        perror("Error executing command");
    }
    return result;
} // end of func

// Function to check if the command executed successfully
int32_t fossil_command_success(fossil_command_t process) {
    int32_t result = fossil_command(process);
    if (result == 0) {
        printf("Command '%s' executed successfully.\n", process);
    } else {
        fprintf(stderr, "Error executing command '%s'.\n", process);
    }
    return result;
} // end of func

// Function to get the output of a command
int32_t fossil_command_output(fossil_command_t process, char *output, size_t output_size) {
#ifdef _WIN32
    FILE *pipe = _popen(process, "r");
    if (!pipe) {
        perror("Error opening pipe");
        return -1;
    }

    size_t bytesRead = fread(output, 1, output_size - 1, pipe);
    output[bytesRead] = '\0';

    if (ferror(pipe)) {
        perror("Error reading from pipe");
        _pclose(pipe);
        return -1;
    }

    int32_t status = _pclose(pipe);
    if (status == -1) {
        perror("Error closing pipe");
    }

    return status;
#else
    int32_t pipe_fd[2];
    pid_t child_pid;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("Error creating pipe");
        return -1;
    }

    // Fork a child process
    if ((child_pid = fork()) == -1) {
        perror("Error forking process");
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return -1;
    }

    if (child_pid == 0) {
        // Child process
        close(pipe_fd[0]);  // Close the read end of the pipe

        // Redirect stdout to the pipe
        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
            perror("Error redirecting stdout");
            exit(EXIT_FAILURE);
        }

        // Close the unused write end of the pipe
        close(pipe_fd[1]);

        // Execute the command
        execl("/bin/sh", "/bin/sh", "-c", process, (char *)NULL);
        perror("Error executing command");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipe_fd[1]);  // Close the write end of the pipe

        // Read the output from the pipe
        size_t bytesRead = read(pipe_fd[0], output, output_size - 1);
        if (bytesRead == (size_t)-1) {
            perror("Error reading from pipe");
            close(pipe_fd[0]);
            waitpid(child_pid, NULL, 0);  // Wait for the child process to complete
            return -1;
        }

        // Null-terminate the output
        output[bytesRead] = '\0';

        close(pipe_fd[0]);  // Close the read end of the pipe

        // Wait for the child process to complete
        waitpid(child_pid, NULL, 0);

        return 0;  // Success
    }
#endif
} // end of func

// Function to check if a command exists and is executable
int32_t fossil_command_exists(fossil_command_t process) {
#ifdef _WIN32
    // On Windows, check if the command exists in the system path
    const char* env_path = getenv("PATH");
    if (env_path != NULL) {
        char path_copy[1024];
        strcpy(path_copy, env_path);

        char* token = strtok(path_copy, _FOSSIL_PATH_SEPARATOR);
        while (token != NULL) {
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s\\%s", token, process);
            if (GetFileAttributes(full_path) != INVALID_FILE_ATTRIBUTES) {
                printf("Command '%s' exists and is executable.\n", process);
                return 1;
            }
            token = strtok(NULL, _FOSSIL_PATH_SEPARATOR);
        }
    }
    fprintf(stderr, "Command '%s' does not exist or is not executable.\n", process);
    return 0;
#else
    // On Unix-like systems, use the access function
    if (access(process, X_OK) == 0) {
        printf("Command '%s' exists and is executable.\n", process);
        return 1;
    } else {
        fprintf(stderr, "Command '%s' does not exist or is not executable.\n", process);
        return 0;
    }
#endif
} // end of function

// Function to concatenate strings safely
void fossil_command_strcat_safe(char *  restrict dest, const char *  restrict src, size_t dest_size) {
    size_t dest_len = strlen(dest);
    size_t src_len = strlen(src);

    // Calculate available space in dest buffer, including null terminator
    size_t space_left = dest_size - dest_len - 1;

    // Copy only the part of src that fits in the remaining space
    size_t copy_len = (src_len < space_left) ? src_len : space_left;

    // Append src to dest
    strncat(dest, src, copy_len);

    // Ensure null-termination
    dest[dest_size - 1] = '\0';
} // end of func

// Function to check if a directory exists
int32_t fossil_command_erase_exists(fossil_command_t path) {
    if (!path) {
        fprintf(stderr, "Error: Null path provided.\n");
        return 0;
    }

    struct stat info;
    if (stat(path, &info) == 0 && S_ISDIR(info.st_mode)) {
        printf("Directory '%s' exists.\n", path);
        return 1;
    } else {
        printf("Directory '%s' does not exist.\n", path);
        return 0;
    }
} // end of func
