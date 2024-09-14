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
#ifndef FOSSIL_LIB_EXIT_H
#define FOSSIL_LIB_EXIT_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// Exit codes
#define FOSSIL_EXIT_SUCCESS 0
#define FOSSIL_EXIT_FAILURE 1

enum {
    FOSSIL_SUCCESS = 0,
    FOSSIL_FAILURE = 1
};

// Function pointer type for cleanup functions
typedef void (*fossil_handle_func_t)(void);

/**
 * @brief Handles the abort signal for the program.
 * 
 * This function is called when the program needs to abort execution 
 * due to an unrecoverable error.
 */
void fossil_handle_abort(void);

/** * @brief Handles normal program exit. * t foss * @param status The exit status code to return to the operating system.
 * 
 * This function is called to perform cleanup and exit the program 
 * with the specified status code.
 */
void fossil_handle_exit(int status);

/** 
 * @brief Handles quick program exit.
 *  
 * @param status The exit status code to return to the operating system.
 * 
 * This function is called to exit the program quickly, bypassing 
 * normal cleanup routines.
 */
void fossil_handle_quick_exit(int status);

/** 
 * @brief Handles immediate program termination.
 * 
 * @param status The exit status code to return to the operating system.
 * 
 * This function is called to terminate the program immediately, 
 * without performing any cleanup.
 */
void fossil_handle__Exit(int status);

/** 
 * @brief Registers a function to be called at program exit.
 * 
 * @param func The function to register for exit handling.
 * 
 * @return An integer indicating success or failure of the registration.
 * 
 * This function allows the user to register a custom function that 
 * will be called when the program exits normally.
 */
int fossil_handle_atexit(fossil_handle_func_t func);

/**
 * @brief Registers a function to be called at quick exit.
 * 
 * @param func The function to register for quick exit handling.
 * 
 * @return An integer indicating success or failure of the registration.
 * 
 * This function allows the user to register a custom function that 
 * will be called when the program exits quickly.
 */
int fossil_handle_at_quick_exit(fossil_handle_func_t func);

#ifdef __cplusplus
}
#endif

#endif /* FOSSIL_LIB_FRAMEWORK_H */
