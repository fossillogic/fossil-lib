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
#ifndef FOSSIL_LIB_CNULLPTR_H
#define FOSSIL_LIB_CNULLPTR_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// null type declaration for compatibility with C11, C23, and C++
#ifndef FOSSIL_CNULL

#if __cplusplus >= 201103L || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
/**
 * @brief Definition for cnull pointers in C++11 and later or C23 and later.
 *
 * In C++11 or later, `cnullptr` is a keyword representing a cnull pointer constant.
 * In C23 or later, `_cnullptr` is recognized in the same way as C++.
 */
    #define cnull    nullptr
    #define cnullptr nullptr
#else
    #if defined(_WIN64) || defined(_WIN32)
/**
 * @brief Definition for cnull pointers on Windows systems.
 *
 * For Windows (both 32-bit and 64-bit), we define `cnull` and `cnullptr` as 0.
 */
    #define cnull    0
    #define cnullptr 0
#else
/**
 * @brief Definition for cnull pointers on POSIX systems, macOS, and embedded systems.
 *
 * For POSIX, macOS, and embedded systems, we define `cnull` and `cnullptr` as a void pointer to 0.
 */
    #define cnull    (void *)(0)
    #define cnullptr (void *)(0)
    #endif
#endif
#endif

#define cterminator '\0'
#define wterminator L'\0'
#define cterm '\0'
#define wterm L'\0'

#ifdef __cplusplus
}
#endif

#endif /* FOSSIL_LIB_FRAMEWORK_H */
