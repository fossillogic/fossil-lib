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
#ifndef FOSSIL_LIB_MEMORY_H
#define FOSSIL_LIB_MEMORY_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Define fossil_memory_t as void*
typedef void* fossil_memory_t;

/**
 * Allocate memory.
 *
 * @param size The size of the memory to allocate.
 * @return A pointer to the allocated memory.
 * @throws Error message and exits if allocation fails.
 */
fossil_memory_t fossil_memory_alloc(size_t size);

/**
 * Reallocate memory.
 *
 * @param ptr A pointer to the previously allocated memory.
 * @param size The new size of the memory to allocate.
 * @return A pointer to the reallocated memory.
 * @throws Error message and exits if reallocation fails or if the pointer is NULL.
 */
fossil_memory_t fossil_memory_realloc(fossil_memory_t ptr, size_t size);

/**
 * Free memory.
 *
 * @param ptr A pointer to the memory to free.
 * @throws Error message and exits if the pointer is NULL.
 */
void fossil_memory_free(fossil_memory_t ptr);

/**
 * Copy memory.
 *
 * @param dest A pointer to the destination memory.
 * @param src A pointer to the source memory.
 * @param size The size of the memory to copy.
 * @return A pointer to the destination memory.
 * @throws Error message and exits if copying fails or if either source or destination is NULL.
 */
fossil_memory_t fossil_memory_copy(fossil_memory_t dest, const fossil_memory_t src, size_t size);

/**
 * Set memory.
 *
 * @param ptr A pointer to the memory to set.
 * @param value The value to set.
 * @param size The size of the memory to set.
 * @return A pointer to the memory.
 * @throws Error message and exits if setting fails or if the pointer is NULL.
 */
fossil_memory_t fossil_memory_set(fossil_memory_t ptr, int32_t value, size_t size);

/**
 * Duplicate memory.
 *
 * @param src A pointer to the memory to duplicate.
 * @param size The size of the memory to duplicate.
 * @return A pointer to the duplicated memory.
 * @throws Error message and exits if duplication fails or if the source is NULL.
 */
fossil_memory_t fossil_memory_dup(const fossil_memory_t src, size_t size);

/**
 * Zero memory.
 *
 * @param ptr A pointer to the memory to zero.
 * @param size The size of the memory to zero.
 * @throws Error message and exits if the pointer is NULL.
 */
void fossil_memory_zero(fossil_memory_t ptr, size_t size);

/**
 * Compare memory.
 *
 * @param ptr1 A pointer to the first memory.
 * @param ptr2 A pointer to the second memory.
 * @param size The size of the memory to compare.
 * @return The result of the comparison.
 * @throws Error message and exits if the pointers are NULL or if the size is zero.
 */
int fossil_memory_compare(const fossil_memory_t ptr1, const fossil_memory_t ptr2, size_t size);

/**
 * Move memory.
 *
 * @param dest A pointer to the destination memory.
 * @param src A pointer to the source memory.
 * @param size The size of the memory to move.
 * @return A pointer to the destination memory.
 * @throws Error message and exits if moving fails or if either source or destination is NULL.
 */
fossil_memory_t fossil_memory_move(fossil_memory_t dest, const fossil_memory_t src, size_t size);

/**
 * Resize memory.
 *
 * @param ptr A pointer to the memory to resize.
 * @param old_size The old size of the memory.
 * @param new_size The new size of the memory.
 * @return A pointer to the resized memory.
 * @throws Error message and exits if resizing fails or if the pointer is NULL.
 */
fossil_memory_t fossil_memory_resize(fossil_memory_t ptr, size_t old_size, size_t new_size);

/**
 * Check if a memory pointer is valid.
 *
 * @param ptr A pointer to the memory.
 * @return 1 if the memory is valid, 0 otherwise.
 */
bool fossil_memory_is_valid(const fossil_memory_t ptr);

#ifdef __cplusplus
}
#endif

#endif /* FOSSIL_LIB_FRAMEWORK_H */
