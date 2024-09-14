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
#include "fossil/lib/regex.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

// Function prototypes
int32_t is_match(const char *text, const char *pattern);

int32_t fossil_regex_create(fossil_regex_t *preg, const char*  pattern) {
    // Input validation: Check if preg or pattern is NULL
    if (preg == NULL || pattern == NULL) {
        return FOSSIL_REGEX_STATUS_FAILURE;
    }

    // Validate pattern length to prevent buffer overflow
    size_t pattern_len = strlen(pattern);
    if (pattern_len == 0 || pattern_len >= FOSSIL_REGEX_LIMIT_PATTERN_LENGTH) {
        return FOSSIL_REGEX_STATUS_FAILURE;
    }

    preg->pattern = pattern;
    preg->matched_substring = NULL;

    return FOSSIL_REGEX_STATUS_SUCCESS;
}

int32_t fossil_regex_match(fossil_regex_t *preg, const char*  text) {
    if (preg == NULL || text == NULL) {
        return FOSSIL_REGEX_STATUS_FAILURE;
    }

    // Call the actual matching function
    int result = is_match(text, preg->pattern);

    preg->matched_substring = result ? text : NULL;

    return result ? FOSSIL_REGEX_STATUS_SUCCESS : FOSSIL_REGEX_STATUS_FAILURE;
}

void fossil_regex_reset(fossil_regex_t *preg) {
    if (preg == NULL) {
        return;
    }

    preg->pattern = NULL;
    preg->matched_substring = NULL;
}

const char *fossil_regex_get_matched_substring(fossil_regex_t *preg) {
    if (preg == NULL) {
        return NULL;
    }
    return preg->matched_substring;
}

const char *fossil_regex_match_and_extract(fossil_regex_t *preg, const char*  text) {
    if (preg == NULL || text == NULL) {
        return NULL;
    }

    if (fossil_regex_match(preg, text) == FOSSIL_REGEX_STATUS_SUCCESS) {
        return fossil_regex_get_matched_substring(preg);
    } else {
        return NULL;
    }
}

// Actual regex matching function
int32_t is_match(const char *text, const char *pattern) {
    if (*pattern == '\0') {
        return *text == '\0';
    }

    if (*(pattern + 1) == '*') {
        return is_match(text, pattern + 2) || (*text != '\0' && (*pattern == '.' || *text == *pattern) && is_match(text + 1, pattern));
    } else {
        return (*text != '\0' && (*pattern == '.' || *text == *pattern) && is_match(text + 1, pattern + 1));
    }
}
