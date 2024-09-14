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
#ifndef FOSSIL_LIB_HOSTSYS_H
#define FOSSIL_LIB_HOSTSYS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
    _FOSSIL_HOSTSYS_SIZE = 256
};

// Structure to represent a host system
typedef struct {
    char os_name[_FOSSIL_HOSTSYS_SIZE];
    char os_version[_FOSSIL_HOSTSYS_SIZE];
    char cpu_model[_FOSSIL_HOSTSYS_SIZE];
    int32_t cpu_cores;
    int64_t total_memory;
    int64_t free_memory;
    bool is_big_endian;
} fossil_hostsystem_t;

/**
 * @brief Retrieves the system information and stores it in the provided fossil_hostsystem_t structure.
 * 
 * This function retrieves various system information such as the operating system name,
 * version, CPU model, number of CPU cores, total memory, and free memory. The information
 * is stored in the provided fossil_hostsystem_t structure.
 * 
 * @param info Pointer to the fossil_hostsystem_t structure where the system information will be stored.
 * @return Returns true if the system information was successfully retrieved, otherwise false.
 */
bool fossil_hostsys_get(fossil_hostsystem_t *info);

/**
 * @brief Prints the system information to the standard output.
 * 
 * This function prints the retrieved system information to the standard output,
 * including the operating system name, version, CPU model, number of CPU cores,
 * total memory, free memory, and endianness.
 * 
 * @param info Pointer to the fossil_hostsystem_t structure containing the system information.
 */
void fossil_hostsys_print(fossil_hostsystem_t *info);

/**
 * @brief Returns a string indicating the endianness of the system.
 * 
 * This function checks the endianness of the system and returns a string indicating
 * whether the system is big endian or little endian.
 * 
 * @param info Pointer to the fossil_hostsystem_t structure containing the system information.
 * @return Returns a string "Big Endian" if the system is big endian, otherwise "Little Endian".
 */
const char* fossil_hostsys_endian(fossil_hostsystem_t *info);

#ifdef __cplusplus
}
#endif

#endif /* FOSSIL_LIB_FRAMEWORK_H */
