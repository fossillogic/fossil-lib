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
#include "fossil/lib/exit.h"
#include <stdlib.h>
#include <stdio.h>

// Static array to track registered functions (optional)
#define MAX_REGISTERED_FUNCS 100
static fossil_handle_func_t registered_funcs[MAX_REGISTERED_FUNCS];
static int func_count = 0;

void fossil_handle_abort(void) {
    fprintf(stderr, "Program aborted unexpectedly.\n");
    abort();
}

void fossil_handle_exit(int status) {
    fprintf(stderr, "Program exiting with status: %d\n", status);
    exit(status);  // Standard exit, will run atexit handlers
}

void fossil_handle_quick_exit(int status) {
    fprintf(stderr, "Program quickly exiting with status: %d\n", status);
    quick_exit(status);  // Quickly exits, but runs at_quick_exit handlers
}

void fossil_handle__Exit(int status) {
    fprintf(stderr, "Program exiting without cleanup, status: %d\n", status);
    _Exit(status);  // Immediately exits without cleanup
}

int fossil_handle_atexit(fossil_handle_func_t func) {
    if (!func) {
        fprintf(stderr, "Error: NULL function pointer cannot be registered with atexit.\n");
        return FOSSIL_EXIT_FAILURE;
    }

    // Check if the function is already registered
    for (int i = 0; i < func_count; ++i) {
        if (registered_funcs[i] == func) {
            fprintf(stderr, "Error: Function already registered with atexit.\n");
            return FOSSIL_EXIT_FAILURE;
        }
    }

    // Register function
    if (atexit(func) != 0) {
        fprintf(stderr, "Error: Could not register atexit function.\n");
        return FOSSIL_EXIT_FAILURE;
    }

    // Store function in the registered list
    if (func_count < MAX_REGISTERED_FUNCS) {
        registered_funcs[func_count++] = func;
    } else {
        fprintf(stderr, "Error: Maximum number of atexit functions reached.\n");
        return FOSSIL_EXIT_FAILURE;
    }

    return FOSSIL_EXIT_SUCCESS;
}

int fossil_handle_at_quick_exit(fossil_handle_func_t func) {
    if (!func) {
        fprintf(stderr, "Error: NULL function pointer cannot be registered with at_quick_exit.\n");
        return FOSSIL_EXIT_FAILURE;
    }

    // Register function for quick exit
    if (at_quick_exit(func) != 0) {
        fprintf(stderr, "Error: Could not register at_quick_exit function.\n");
        return FOSSIL_EXIT_FAILURE;
    }

    return FOSSIL_EXIT_SUCCESS;
}
