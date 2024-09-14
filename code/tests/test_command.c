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

// Test cases for fossil_command functions
FOSSIL_TEST(test_fossil_command_success) {
    ASSUME_ITS_EQUAL_I32(fossil_command_success("success"), 1);
    ASSUME_ITS_EQUAL_I32(fossil_command_success("failure"), 0);
    ASSUME_ITS_EQUAL_I32(fossil_command_success("unknown"), 0);
}

FOSSIL_TEST(test_fossil_command_output) {
    char output[256];
    
    ASSUME_ITS_EQUAL_I32(fossil_command_output("success", output, sizeof(output)), 0);
    ASSUME_ITS_EQUAL_CSTR(output, "Command executed successfully.");
    
    ASSUME_ITS_EQUAL_I32(fossil_command_output("failure", output, sizeof(output)), 1);
    ASSUME_ITS_EQUAL_CSTR(output, "Command failed to execute.");
    
    ASSUME_ITS_EQUAL_I32(fossil_command_output("unknown", output, sizeof(output)), -1);
}

FOSSIL_TEST(test_fossil_command_exists) {
    ASSUME_ITS_EQUAL_I32(fossil_command_exists("success"), 1);
    ASSUME_ITS_EQUAL_I32(fossil_command_exists("failure"), 1);
    ASSUME_ITS_EQUAL_I32(fossil_command_exists("unknown"), 0);
}

FOSSIL_TEST(test_fossil_command_erase_exists) {
    ASSUME_ITS_EQUAL_I32(fossil_command_erase_exists("success"), 1);
    ASSUME_ITS_EQUAL_I32(fossil_command_erase_exists("failure"), 1);
    ASSUME_ITS_EQUAL_I32(fossil_command_erase_exists("unknown"), 0);
}

FOSSIL_TEST(test_fossil_command_strcat_safe) {
    char dest[256] = "Initial ";
    const char *src = "Concatenated";
    
    fossil_command_strcat_safe(dest, src, sizeof(dest));
    ASSUME_ITS_EQUAL_CSTR(dest, "Initial Concatenated");
    
    // Test edge case: concatenation with a buffer that is too small
    char small_dest[10] = "Initial ";
    fossil_command_strcat_safe(small_dest, src, sizeof(small_dest));
    ASSUME_ITS_EQUAL_CSTR(small_dest, "Initial Con");
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_command_tests) {
    ADD_TEST(test_fossil_command_success);
    ADD_TEST(test_fossil_command_output);
    ADD_TEST(test_fossil_command_exists);
    ADD_TEST(test_fossil_command_erase_exists);
    ADD_TEST(test_fossil_command_strcat_safe);
}
