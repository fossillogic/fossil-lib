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
#include <fossil/unittest/framework.h>
#include <fossil/xassume.h>

#include "fossil/lib/framework.h"

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(test_fossil_command) {
    int32_t result;

    // Test valid command
    result = fossil_command("echo Hello World");
    ASSUME_ITS_EQUAL_I32(0, result);

    // Test invalid command
    result = fossil_command("invalid_command");
    ASSUME_NOT_EQUAL_I32(0, result);
}

FOSSIL_TEST(test_fossil_command_success) {
    int32_t result;

    // Test valid command
    result = fossil_command_success("echo Hello World");
    ASSUME_ITS_EQUAL_I32(0, result);

    // Test invalid command
    result = fossil_command_success("invalid_command");
    ASSUME_NOT_EQUAL_I32(0, result);
}

FOSSIL_TEST(test_fossil_command_output) {
    char output[128];
    int32_t result;

    // Test valid command
    result = fossil_command_output("echo Hello World", output, sizeof(output));
    ASSUME_ITS_EQUAL_I32(0, result);

#ifdef _WIN32
    // On Windows, the newline is "\r\n" instead of "\n"
    ASSUME_ITS_EQUAL_CSTR("Hello World\n", output);
#else
    ASSUME_ITS_EQUAL_CSTR("Hello World\n", output);
#endif
}

FOSSIL_TEST(test_fossil_command_exists) {
    int32_t result;

#ifdef _WIN32
    // Use "where" on Windows
    result = fossil_command_exists("where echo");
#else
    // Use "which" on Unix-like systems
    result = fossil_command_exists("which echo");
#endif

    ASSUME_ITS_EQUAL_I32(0, result);

    // Test a non-existing command
#ifdef _WIN32
    result = fossil_command_exists("where invalid_command");
#else
    result = fossil_command_exists("which invalid_command");
#endif
    ASSUME_ITS_EQUAL_I32(0, result);
}

FOSSIL_TEST(test_fossil_command_strcat_safe) {
    char buffer[16];

    // Initialize buffer
    strcpy(buffer, "Hello");

    // Test appending within buffer limits
    fossil_command_strcat_safe(buffer, " World", sizeof(buffer));
    ASSUME_ITS_EQUAL_CSTR("Hello World", buffer);

    // Test appending with truncation
    fossil_command_strcat_safe(buffer, "12345678901234567890", sizeof(buffer));
    ASSUME_ITS_EQUAL_CSTR("Hello World1234", buffer);
}

FOSSIL_TEST(test_fossil_command_erase_exists) {
    int32_t result;

#ifdef _WIN32
    // Use a different path on Windows, e.g., "C:\\"
    result = fossil_command_erase_exists("C:\\");
#else
    // Use "/tmp" on Unix-like systems
    result = fossil_command_erase_exists("/tmp");
#endif

    ASSUME_ITS_EQUAL_I32(1, result);

    // Test non-existing directory
    result = fossil_command_erase_exists("non_existing_directory");
    ASSUME_ITS_EQUAL_I32(0, result);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_command_tests) {
    ADD_TEST(test_fossil_command);
    ADD_TEST(test_fossil_command_success);
    ADD_TEST(test_fossil_command_output);
    ADD_TEST(test_fossil_command_exists);
    ADD_TEST(test_fossil_command_strcat_safe);
    ADD_TEST(test_fossil_command_erase_exists);
}
