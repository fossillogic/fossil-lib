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
    ASSUME_ITS_EQUAL_I32(fossil_command_success("meson --version"), 0);  // Expect success
}

FOSSIL_TEST(test_fossil_command_output) {
    char output[256];

    // Test known successful command for Meson
    ASSUME_ITS_EQUAL_I32(fossil_command_output("meson --version", output, sizeof(output)), 0);
}

FOSSIL_TEST(test_fossil_command_exists) {
    // Test known commands for Meson
    ASSUME_ITS_EQUAL_I32(fossil_command_exists("meson"), 0);  // Command should exist
}

FOSSIL_TEST(test_fossil_command_erase_exists) {
    // Test known commands for Meson
    ASSUME_ITS_EQUAL_I32(fossil_command_erase_exists("meson --version"), 0);  // Command should exist
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_command_tests) {
    ADD_TEST(test_fossil_command_success);
    ADD_TEST(test_fossil_command_output);
    ADD_TEST(test_fossil_command_exists);
    ADD_TEST(test_fossil_command_erase_exists);
}
