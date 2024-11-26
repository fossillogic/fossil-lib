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
FOSSIL_TEST_SUITE(cpp_args_suite);

// Setup function for the test suite
FOSSIL_SETUP(cpp_args_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(cpp_args_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_arg_parse_has) {
    // Test fossil_arg_parse_has function
    fossil_option_t options[] = {
        {"option1", COPTION_TYPE_BOOL, {.bool_val = 0}, cnull, 0, 0},
        {"option2", COPTION_TYPE_INT, {.int_val = 42}, cnull, 0, 0}
    };
    int num_options = sizeof(options) / sizeof(options[0]);

    // Assuming fossil_arg_parse_has returns 1 for the existing option
    ASSUME_ITS_EQUAL_I32(0, fossil_arg_parse_has(options, num_options, "option1"));
}

FOSSIL_TEST_CASE(cpp_test_arg_parse) {
    // Test fossil_arg_parse function
    const char* argv[] = {"program", "-number", "42", "-name", "John", "-flag", "-choice", "choice2", "-feature", "enable"};
    const int argc = sizeof(argv) / sizeof(argv[0]);

    fossil_command_line_t cmd = {argc, (char **)argv};
    
    fossil_option_t options[] = {
        {"option1", COPTION_TYPE_INT, {.int_val = 0}, cnull, 0, 0},
        {"option2", COPTION_TYPE_BOOL, {.bool_val = 0}, cnull, 0, 0}
    };
    int num_options = sizeof(options) / sizeof(options[0]);

    // Assuming fossil_arg_parse modifies the options array
    fossil_arg_parse(&cmd, options, num_options);

    ASSUME_ITS_EQUAL_I32(0, options[0].value.int_val);
    ASSUME_ITS_EQUAL_I32(0, options[1].value.bool_val);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(cpp_commandline_tests) {
    FOSSIL_TEST_ADD(cpp_args_suite, cpp_test_arg_parse_has);
    FOSSIL_TEST_ADD(cpp_args_suite, cpp_test_arg_parse);

    FOSSIL_TEST_REGISTER(cpp_args_suite);
}
