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
#ifndef FOSSIL_LIB_COMMAND_H
#define FOSSIL_LIB_COMMAND_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Define a typedef for char* to make the code more readable
typedef char* fossil_command_t;

/**
 * Execute a command and return the result.
 *
 * @param process The command to be executed.
 * @return        The result of the command execution.
 */
int32_t fossil_command(fossil_command_t process);

/**
 * Check if a command execution was successful.
 *
 * @param process The command to be checked.
 * @return        1 if the command was successful, 0 otherwise.
 */
int32_t fossil_command_success(fossil_command_t process);

/**
 * Retrieve the output of a command execution.
 *
 * @param process     The command to retrieve output from.
 * @param output      Buffer to store the output.
 * @param output_size Size of the output buffer.
 * @return            The result of the command execution.
 */
int32_t fossil_command_output(fossil_command_t process, char * output, size_t output_size);

/**
 * Check if a command exists.
 *
 * @param process The command to be checked.
 * @return        1 if the command exists, 0 otherwise.
 */
int32_t fossil_command_exists(fossil_command_t process);

/**
 * Erase a command and check if it exists.
 *
 * @param path The command to be erased.
 * @return     1 if the command exists, 0 otherwise.
 */
int32_t fossil_command_erase_exists(fossil_command_t path);

/**
 * Safely concatenate two strings into a destination buffer.
 *
 * @param dest      The destination buffer for the concatenated strings.
 * @param src       The source string to be concatenated.
 * @param dest_size The size of the destination buffer.
 */
void fossil_command_strcat_safe(char * dest, const char * src, size_t dest_size);

#ifdef __cplusplus
}
#endif

#endif /* FOSSIL_LIB_FRAMEWORK_H */
