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
#include <fossil/unittest/assume.h>

#include "fossil/lib/framework.h"

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(test_fossil_arg_parse_has) {
    // Test fossil_arg_parse_has function
    fossil_option_t options[] = {
        {"option1", COPTION_TYPE_BOOL, {.bool_val = 0}, cnull, 0, 0},
        {"option2", COPTION_TYPE_INT, {.int_val = 42}, cnull, 0, 0}
    };
    int num_options = sizeof(options) / sizeof(options[0]);

    // Assuming fossil_arg_parse_has returns 1 for the existing option
    ASSUME_ITS_EQUAL_I32(0, fossil_arg_parse_has(options, num_options, "option1"));
}

FOSSIL_TEST(test_fossil_arg_parse) {
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

FOSSIL_TEST_GROUP(c_commandline_tests) {
    ADD_TEST(test_fossil_arg_parse_has);
    ADD_TEST(test_fossil_arg_parse);
}
