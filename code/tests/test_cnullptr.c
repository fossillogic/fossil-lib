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

#ifndef cnull
#error "cnull is not defined."
#endif

#ifndef cnullptr
#error "cnullptr is not defined."
#endif

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test
// * * * * * * * * * * * * * * * * * * * * * * * *

// Test cases for cnull
FOSSIL_TEST(test_cnull_definition) {
    // Test cnull definition
#if __cplusplus >= 201103L || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
    // C++11 or later, C23 or later
    ASSUME_ITS_EQUAL_PTR(cnull, nullptr);
    ASSUME_ITS_EQUAL_PTR(cnullptr, nullptr);
#else
    // Pre-C++11 or C23
    #if defined(_WIN64) || defined(_WIN32)
    // Windows
        ASSUME_ITS_EQUAL_PTR(cnull, 0);
        ASSUME_ITS_EQUAL_PTR(cnullptr, 0);
    #else
    // POSIX, macOS, and embedded systems
        ASSUME_ITS_EQUAL_PTR(cnull, (void *)(0));
        ASSUME_ITS_EQUAL_PTR(cnullptr, (void *)(0));
    #endif
#endif
}

// Test cases for cterminator and related constants
FOSSIL_TEST(test_cterminator_definition) {
    // Check if the terminator constants are defined correctly
    ASSUME_ITS_EQUAL_CHAR(cterminator, '\0');
    ASSUME_ITS_EQUAL_WCHAR(wterminator, L'\0');
    ASSUME_ITS_EQUAL_CHAR(cterm, '\0');
    ASSUME_ITS_EQUAL_WCHAR(wterm, L'\0');
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(cnull_tests) {
    ADD_TEST(test_cnull_definition);
    ADD_TEST(test_cterminator_definition);
}
