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

FOSSIL_TEST(test_memory_alloc) {
    size_t size = 10;
    fossil_memory_t ptr = fossil_memory_alloc(size);
    ASSUME_NOT_CNULL(ptr);
    fossil_memory_free(ptr); // Cleanup
}

FOSSIL_TEST(test_memory_realloc) {
    size_t size = 10;
    fossil_memory_t ptr = fossil_memory_alloc(size);
    ASSUME_NOT_CNULL(ptr);

    size *= 2;
    ptr = fossil_memory_realloc(ptr, size);
    ASSUME_NOT_CNULL(ptr);

    fossil_memory_free(ptr); // Cleanup
}

FOSSIL_TEST(test_memory_dup) {
    size_t size = 10;
    fossil_memory_t src = fossil_memory_alloc(size);
    ASSUME_NOT_CNULL(src);

    fossil_memory_t dest = fossil_memory_dup(src, size);
    ASSUME_NOT_CNULL(dest);

    ASSUME_ITS_TRUE(memcmp(src, dest, size) == 0); // Ensure that both blocks are identical
    fossil_memory_free(src);
    fossil_memory_free(dest); // Cleanup
}

FOSSIL_TEST(test_memory_zero) {
    size_t size = 10;
    fossil_memory_t ptr = fossil_memory_alloc(size);
    ASSUME_NOT_CNULL(ptr);

    fossil_memory_zero(ptr, size);
    for (size_t i = 0; i < size; ++i) {
        ASSUME_ITS_TRUE(((unsigned char*)ptr)[i] == 0); // Ensure all bytes are zero
    }

    fossil_memory_free(ptr); // Cleanup
}

FOSSIL_TEST(test_memory_alloc_aligned) {
    size_t size = 16;
    size_t alignment = 16; // Alignment to 16 bytes
    fossil_memory_t ptr = fossil_memory_alloc_aligned(size, alignment);
    ASSUME_NOT_CNULL(ptr);
    ASSUME_ITS_TRUE(((uintptr_t)ptr % alignment) == 0); // Ensure alignment

    fossil_memory_free(ptr); // Cleanup
}

FOSSIL_TEST(test_memory_compare) {
    size_t size = 10;
    fossil_memory_t ptr1 = fossil_memory_alloc(size);
    fossil_memory_t ptr2 = fossil_memory_alloc(size);
    ASSUME_NOT_CNULL(ptr1);
    ASSUME_NOT_CNULL(ptr2);

    fossil_memory_set(ptr1, 0xAA, size); // Set all bytes to 0xAA
    fossil_memory_set(ptr2, 0xAA, size); // Set all bytes to 0xAA
    ASSUME_ITS_TRUE(fossil_memory_compare(ptr1, ptr2, size) == 0); // Should be equal

    fossil_memory_set(ptr2, 0xBB, size); // Change ptr2
    ASSUME_ITS_TRUE(fossil_memory_compare(ptr1, ptr2, size) != 0); // Should not be equal

    fossil_memory_free(ptr1);
    fossil_memory_free(ptr2); // Cleanup
}

FOSSIL_TEST(test_memory_move) {
    size_t size = 10;
    fossil_memory_t src = fossil_memory_alloc(size);
    ASSUME_NOT_CNULL(src);

    fossil_memory_t dest = fossil_memory_alloc(size);
    ASSUME_NOT_CNULL(dest);

    fossil_memory_set(src, 0xAA, size);
    fossil_memory_move(dest, src, size);
    ASSUME_ITS_TRUE(memcmp(dest, src, size) == 0); // Ensure memory is moved correctly

    fossil_memory_free(src);
    fossil_memory_free(dest); // Cleanup
}

FOSSIL_TEST(test_memory_resize) {
    size_t size = 10;
    fossil_memory_t ptr = fossil_memory_alloc(size);
    ASSUME_NOT_CNULL(ptr);

    ptr = fossil_memory_resize(ptr, size, size * 2);
    ASSUME_NOT_CNULL(ptr); // Ensure resizing works

    fossil_memory_free(ptr); // Cleanup
}

FOSSIL_TEST(test_memory_is_valid) {
    fossil_memory_t ptr = fossil_memory_alloc(10);
    ASSUME_ITS_TRUE(fossil_memory_is_valid(ptr)); // Should be valid
    ASSUME_ITS_TRUE(!fossil_memory_is_valid(NULL)); // NULL should not be valid

    fossil_memory_free(ptr); // Cleanup
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_memory_tests) {
    ADD_TEST(test_memory_alloc);
    ADD_TEST(test_memory_realloc);
    ADD_TEST(test_memory_dup);
    ADD_TEST(test_memory_zero);
    ADD_TEST(test_memory_alloc_aligned);
    ADD_TEST(test_memory_compare);
    ADD_TEST(test_memory_move);
    ADD_TEST(test_memory_resize);
    ADD_TEST(test_memory_is_valid);
}
