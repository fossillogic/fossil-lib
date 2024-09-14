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
#ifndef FOSSIL_LIB_REGEX_H
#define FOSSIL_LIB_REGEX_H

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

// Enumeration for regex operation statuses
enum {
    FOSSIL_REGEX_STATUS_SUCCESS = 0,  // Operation succeeded
    FOSSIL_REGEX_STATUS_FAILURE = -1  // Operation failed
};

// Enumeration for regex limits
enum {
    FOSSIL_REGEX_LIMIT_PATTERN_LENGTH = 255  // Maximum length of regex pattern
};

// Structure to hold regex pattern and matched substring, with optional threading support
typedef struct {
    const char *pattern;                // Pointer to the regex pattern
    const char *matched_substring;      // Pointer to the matched substring

    #ifdef _WIN32
        // Mutex for Windows to ensure thread-safe operations
        HANDLE mutex;
    #else
        // Mutex for POSIX to ensure thread-safe operations
        pthread_mutex_t mutex;
    #endif
} fossil_regex_t;

/**
 * Create a new regex pattern instance.
 *
 * @param preg    Pointer to the fossil_regex_t structure to store the created regex pattern.
 * @param pattern The regex pattern to be compiled.
 * @return        0 on success, non-zero on failure.
 */
int32_t fossil_regex_create(fossil_regex_t *preg, const char*  pattern);

/**
 * Match a text against a compiled regex pattern.
 *
 * @param preg Pointer to the fossil_regex_t structure containing the compiled pattern.
 * @param text The text to be matched against the regex pattern.
 * @return     0 if there is a match, non-zero otherwise.
 */
int32_t fossil_regex_match(fossil_regex_t *preg, const char*  text);

/**
 * Reset the regex pattern instance to the initial state.
 *
 * @param preg Pointer to the fossil_regex_t structure.
 */
void fossil_regex_reset(fossil_regex_t *preg);

/**
 * Match a text against a compiled regex pattern and extract the matched substring.
 *
 * @param preg Pointer to the fossil_regex_t structure containing the compiled pattern.
 * @param text The text to be matched against the regex pattern.
 * @return     A constant string containing the matched substring or NULL if no match.
 */
const char *fossil_regex_match_and_extract(fossil_regex_t *preg, const char*  text);

/**
 * Get the matched substring from the last successful match.
 *
 * @param preg Pointer to the fossil_regex_t structure.
 * @return     A constant string containing the matched substring or NULL if no match.
 */
const char *fossil_regex_get_matched_substring(fossil_regex_t *preg);

#ifdef __cplusplus
}
#endif

#endif /* FOSSIL_LIB_FRAMEWORK_H */
