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

// Test cases for fossil_regex functions
FOSSIL_TEST(test_fossil_regex_create) {
    fossil_regex_t regex;
    ASSUME_ITS_EQUAL_I32(fossil_regex_create(&regex, "test"), FOSSIL_REGEX_STATUS_SUCCESS);
    
    // Check if the pattern is correctly set
    ASSUME_ITS_EQUAL_CSTR(regex.pattern, "test");
    
    // Check mutex initialization
    #ifdef _WIN32
    ASSUME_NOT_CNULL(regex.mutex);
    #else
    pthread_mutex_destroy(&regex.mutex); // Clean up
    #endif
}

FOSSIL_TEST(test_fossil_regex_match) {
    fossil_regex_t regex;
    fossil_regex_create(&regex, "pattern");
    
    ASSUME_ITS_EQUAL_I32(fossil_regex_match(&regex, "this is a pattern"), FOSSIL_REGEX_STATUS_SUCCESS);
    ASSUME_ITS_EQUAL_I32(fossil_regex_match(&regex, "no match here"), FOSSIL_REGEX_STATUS_FAILURE);
    
    fossil_regex_reset(&regex);
}

FOSSIL_TEST(test_fossil_regex_match_and_extract) {
    fossil_regex_t regex;
    fossil_regex_create(&regex, "extract");

    ASSUME_ITS_EQUAL_CSTR(fossil_regex_match_and_extract(&regex, "extract this text"), "extract");
    ASSUME_ITS_EQUAL_PTR(fossil_regex_match_and_extract(&regex, "no match"), NULL);
    
    // Test extraction
    ASSUME_ITS_EQUAL_CSTR(fossil_regex_get_matched_substring(&regex), "extract");

    fossil_regex_reset(&regex);
}

FOSSIL_TEST(test_fossil_regex_reset) {
    fossil_regex_t regex;
    fossil_regex_create(&regex, "reset");

    fossil_regex_match_and_extract(&regex, "reset this text");
    ASSUME_ITS_EQUAL_CSTR(fossil_regex_get_matched_substring(&regex), "reset");

    fossil_regex_reset(&regex);
    ASSUME_ITS_EQUAL_PTR(fossil_regex_get_matched_substring(&regex), NULL);
}

FOSSIL_TEST(test_fossil_regex_limit_pattern_length) {
    char long_pattern[FOSSIL_REGEX_LIMIT_PATTERN_LENGTH + 10];
    memset(long_pattern, 'a', sizeof(long_pattern) - 1);
    long_pattern[sizeof(long_pattern) - 1] = '\0';

    fossil_regex_t regex;
    ASSUME_ITS_EQUAL_I32(fossil_regex_create(&regex, long_pattern), FOSSIL_REGEX_STATUS_FAILURE);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_regex_tests) {
    ADD_TEST(test_fossil_regex_create);
    ADD_TEST(test_fossil_regex_match);
    ADD_TEST(test_fossil_regex_match_and_extract);
    ADD_TEST(test_fossil_regex_reset);
    ADD_TEST(test_fossil_regex_limit_pattern_length);
}
