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

FOSSIL_TEST(test_fossil_command_success) {
    // Test known successful command for Meson
    ASSUME_ITS_EQUAL_I32(fossil_command_success("meson --version"), 1);  // Expect success
    ASSUME_ITS_EQUAL_I32(fossil_command_success("nonexistent_command"), 0);  // Expect failure
}

FOSSIL_TEST(test_fossil_command_output) {
    char output[256];

    // Test known successful command for Meson
    ASSUME_ITS_EQUAL_I32(fossil_command_output("meson --version", output, sizeof(output)), 0);
    ASSUME_ITS_EQUAL_CSTR(output, "Expected version output here");  // Replace with actual expected output

    // Test a command known to fail
    ASSUME_ITS_EQUAL_I32(fossil_command_output("nonexistent_command", output, sizeof(output)), 1);
    ASSUME_ITS_EQUAL_CSTR(output, "Command failed to execute.");  // Replace with actual error message
}

FOSSIL_TEST(test_fossil_command_exists) {
    // Test known commands for Meson
    ASSUME_ITS_EQUAL_I32(fossil_command_exists("meson --version"), 1);  // Command should exist
    ASSUME_ITS_EQUAL_I32(fossil_command_exists("nonexistent_command"), 0);  // Command should not exist
}

FOSSIL_TEST(test_fossil_command_erase_exists) {
    // Test known commands for Meson
    ASSUME_ITS_EQUAL_I32(fossil_command_erase_exists("meson --version"), 1);  // Command should exist
    ASSUME_ITS_EQUAL_I32(fossil_command_erase_exists("nonexistent_command"), 0);  // Command should not exist
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
