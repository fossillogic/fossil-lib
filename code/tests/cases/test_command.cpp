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
#include <fossil/test/framework.h>

#include "fossil/lib/framework.h"

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_TEST_SUITE(cpp_command_suite);

// Setup function for the test suite
FOSSIL_SETUP(cpp_command_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(cpp_command_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_command) {
    int32_t result;

    // Test valid command
    result = fossil_command((char *)"echo Hello World");
    ASSUME_ITS_EQUAL_I32(0, result);

    // Test invalid command
    result = fossil_command((char *)"invalid_command");
    ASSUME_NOT_EQUAL_I32(0, result);
}

FOSSIL_TEST_CASE(cpp_test_command_success) {
    int32_t result;

    // Test valid command
    result = fossil_command_success((char *)"echo Hello World");
    ASSUME_ITS_EQUAL_I32(0, result);

    // Test invalid command
    result = fossil_command_success((char *)"invalid_command");
    ASSUME_NOT_EQUAL_I32(0, result);
}

FOSSIL_TEST_CASE(cpp_test_command_output) {
    char output[128];
    int32_t result;

    // Test valid command
    result = fossil_command_output((char *)"echo Hello World", output, sizeof(output));
    ASSUME_ITS_EQUAL_I32(0, result);

#ifdef _WIN32
    // On Windows, the newline is "\r\n" instead of "\n"
    ASSUME_ITS_EQUAL_CSTR("Hello World\n", output);
#else
    ASSUME_ITS_EQUAL_CSTR("Hello World\n", output);
#endif
}

FOSSIL_TEST_CASE(cpp_test_command_exists) {
    int32_t result;

#ifdef _WIN32
    // Use "where" on Windows
    result = fossil_command_exists((char *)"where echo");
#else
    // Use "which" on Unix-like systems
    result = fossil_command_exists((char *)"which echo");
#endif

    ASSUME_ITS_EQUAL_I32(0, result);

    // Test a non-existing command
#ifdef _WIN32
    result = fossil_command_exists((char *)"where invalid_command");
#else
    result = fossil_command_exists((char *)"which invalid_command");
#endif
    ASSUME_ITS_EQUAL_I32(0, result);
}

FOSSIL_TEST_CASE(cpp_test_command_strcat_safe) {
    char buffer[16];

    // Initialize buffer
    strcpy(buffer, "Hello");

    // Test appending within buffer limits
    fossil_command_strcat_safe(buffer, (char *)" World", sizeof(buffer));
    ASSUME_ITS_EQUAL_CSTR("Hello World", buffer);

    // Test appending with truncation
    fossil_command_strcat_safe(buffer, (char *)"12345678901234567890", sizeof(buffer));
    ASSUME_ITS_EQUAL_CSTR("Hello World1234", buffer);
}

FOSSIL_TEST_CASE(cpp_test_command_erase_exists) {
    int32_t result;

#ifdef _WIN32
    // Use a different path on Windows, e.g., "C:\\"
    result = fossil_command_erase_exists((char *)"C:\\");
#else
    // Use "/tmp" on Unix-like systems
    result = fossil_command_erase_exists((char *)"/tmp");
#endif

    ASSUME_ITS_EQUAL_I32(1, result);

    // Test non-existing directory
    result = fossil_command_erase_exists((char *)"non_existing_directory");
    ASSUME_ITS_EQUAL_I32(0, result);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_command_tests) {
#ifdef __unix__
    FOSSIL_TEST_ADD(cpp_command_suite, cpp_test_command);
    FOSSIL_TEST_ADD(cpp_command_suite, cpp_test_command_success);
    FOSSIL_TEST_ADD(cpp_command_suite, cpp_test_command_output);
    FOSSIL_TEST_ADD(cpp_command_suite, cpp_test_command_exists);
    FOSSIL_TEST_ADD(cpp_command_suite, cpp_test_command_strcat_safe);
    FOSSIL_TEST_ADD(cpp_command_suite, cpp_test_command_erase_exists);
#else
    // test cases need to be updated to adress the Windows platform
    FOSSIL_TEST_SKIP(cpp_test_command, "Test case not supported on Windows");
    FOSSIL_TEST_SKIP(cpp_test_command_success, "Test case not supported on Windows");
    FOSSIL_TEST_SKIP(cpp_test_command_output, "Test case not supported on Windows");
    FOSSIL_TEST_SKIP(cpp_test_command_exists, "Test case not supported on Windows");
    FOSSIL_TEST_SKIP(cpp_test_command_strcat_safe, "Test case not supported on Windows");
    FOSSIL_TEST_SKIP(cpp_test_command_erase_exists, "Test case not supported on Windows");
#endif
    FOSSIL_TEST_REGISTER(cpp_command_suite);
}
