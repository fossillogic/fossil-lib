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
FOSSIL_TEST_SUITE(c_host_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_host_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_host_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_test_hostsys_get) {
    fossil_hostsystem_t info;
    fossil_hostsys_get(&info);
    ASSUME_NOT_EQUAL_CSTR("", info.os_name);
    ASSUME_NOT_EQUAL_CSTR("", info.os_version);
}

FOSSIL_TEST_CASE(c_test_hostsys_endian) {
    fossil_hostsystem_t info;
    fossil_hostsys_get(&info);
    ASSUME_ITS_EQUAL_CSTR(fossil_hostsys_endian(&info), info.is_big_endian ? "Big Endian" : "Little Endian");
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_hostsys_tests) {
    FOSSIL_TEST_ADD(c_hostsys_suite, c_test_hostsys_get);
    FOSSIL_TEST_ADD(c_hostsys_suite, c_test_hostsys_endian);

    FOSSIL_TEST_REGISTER(c_hostsys_suite);
}
