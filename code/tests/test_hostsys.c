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

FOSSIL_TEST(test_fossil_hostsys_get) {
    fossil_hostsystem_t info;
    fossil_hostsys_get(&info);
    ASSUME_NOT_EQUAL_CSTR("", info.os_name);
    ASSUME_NOT_EQUAL_CSTR("", info.os_version);
}

FOSSIL_TEST(test_fossil_hostsys_endian) {
    fossil_hostsystem_t info;
    fossil_hostsys_get(&info);
    ASSUME_ITS_EQUAL_CSTR(fossil_hostsys_endian(&info), info.is_big_endian ? "Big Endian" : "Little Endian");
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_hostsys_tests) {
    ADD_TEST(test_fossil_hostsys_get);
    ADD_TEST(test_fossil_hostsys_endian);
}
