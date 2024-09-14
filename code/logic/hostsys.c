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
#include "fossil/lib/hostsys.h"

#ifdef _WIN32
    #include <windows.h>
    #include <tchar.h>
    #include <lmcons.h>
#elif __linux__
    #include <sys/utsname.h>
    #include <unistd.h>
    #include <sys/sysinfo.h>
#elif __APPLE__
    #include <sys/utsname.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/sysctl.h>
#endif

static bool fossil_hostsys_get_endian(fossil_hostsystem_t *info) {
    unsigned int num = 1;
    char *endian_check = (char*)&num;

    if (*endian_check == 1) {
        info->is_big_endian = false;
    } else {
        info->is_big_endian = true;
    }

    return true;
}

#ifdef _WIN32
static bool fossil_hostsys_get_windows(fossil_hostsystem_t *info) {
    OSVERSIONINFO osvi;
    SYSTEM_INFO si;
    MEMORYSTATUSEX memInfo;

    memset(info, 0, sizeof(fossil_hostsystem_t));
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    
    if (!GetVersionEx(&osvi)) {
        fprintf(stderr, "Error getting Windows version information\n");
        return false;
    }

    strncpy(info->os_name, "Windows", sizeof(info->os_name));
    snprintf(info->os_version, sizeof(info->os_version), "%ld.%ld",
             osvi.dwMajorVersion, osvi.dwMinorVersion);

    GetNativeSystemInfo(&si);
    snprintf(info->cpu_model, sizeof(info->cpu_model), "Intel");

    info->cpu_cores = si.dwNumberOfProcessors;

    if (!GlobalMemoryStatusEx(&memInfo)) {
        fprintf(stderr, "Error getting memory information\n");
        return false;
    }

    info->total_memory = memInfo.ullTotalPhys / (1024 * 1024);  // in MB
    info->free_memory = memInfo.ullAvailPhys / (1024 * 1024);  // in MB

    return true;
}

#elif defined(__linux__)
static bool fossil_hostsys_get_linux(fossil_hostsystem_t *info) {
    struct utsname unameData;
    FILE *cpuinfo;
    char line[256];

    memset(info, 0, sizeof(fossil_hostsystem_t));

    if (uname(&unameData) != 0) {
        fprintf(stderr, "Error getting uname information\n");
        return false;
    }

    strncpy(info->os_name, unameData.sysname, sizeof(info->os_name));
    strncpy(info->os_version, unameData.release, sizeof(info->os_version));

    cpuinfo = fopen("/proc/cpuinfo", "r");
    if (cpuinfo) {
        while (fgets(line, sizeof(line), cpuinfo)) {
            if (strstr(line, "model name")) {
                char *pos = strchr(line, ':');
                if (pos) {
                    strncpy(info->cpu_model, pos + 2, sizeof(info->cpu_model));
                    break;
                }
            }
        }
        fclose(cpuinfo);
    } else {
        fprintf(stderr, "Error opening /proc/cpuinfo\n");
        return false;
    }

    info->cpu_cores = sysconf(_SC_NPROCESSORS_ONLN);

    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    info->total_memory = pages * page_size / (1024 * 1024);  // in MB

    struct sysinfo memInfo;
    if (sysinfo(&memInfo) == 0) {
        info->free_memory = memInfo.freeram / (1024 * 1024);  // in MB
    } else {
        fprintf(stderr, "Error getting memory information\n");
        return false;
    }

    return true;
}

#elif defined(__APPLE__)
#include <mach/mach.h>

static bool fossil_hostsys_get_macos(fossil_hostsystem_t *info) {
    struct utsname unameData;
    memset(info, 0, sizeof(fossil_hostsystem_t));

    if (uname(&unameData) != 0) {
        fprintf(stderr, "Error getting uname information\n");
        return false;
    }

    strncpy(info->os_name, unameData.sysname, sizeof(info->os_name));
    strncpy(info->os_version, unameData.release, sizeof(info->os_version));

    // Get CPU model
    int mib[2] = {CTL_HW, HW_MODEL};
    size_t len = sizeof(info->cpu_model);
    if (sysctl(mib, 2, info->cpu_model, &len, NULL, 0) != 0) {
        fprintf(stderr, "Error getting CPU model information using sysctl\n");
        return false;
    }

    // Get number of CPU cores
    mib[1] = HW_NCPU;
    len = sizeof(info->cpu_cores);
    if (sysctl(mib, 2, &info->cpu_cores, &len, NULL, 0) != 0) {
        fprintf(stderr, "Error getting CPU cores information using sysctl\n");
        return false;
    }

    // Get total memory
    mib[1] = HW_MEMSIZE;
    len = sizeof(info->total_memory);
    if (sysctl(mib, 2, &info->total_memory, &len, NULL, 0) != 0) {
        fprintf(stderr, "Error getting total memory information using sysctl\n");
        return false;
    }
    info->total_memory /= (1024 * 1024); // Convert to MB

    // Get free memory using mach API
    mach_port_t host_port = mach_host_self();
    mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
    vm_statistics_data_t vm_stats;

    if (host_statistics(host_port, HOST_VM_INFO, (host_info_t)&vm_stats, &count) != KERN_SUCCESS) {
        fprintf(stderr, "Error getting free memory information using mach API\n");
        return false;
    }
    info->free_memory = (vm_stats.free_count * vm_page_size) / (1024 * 1024); // Convert to MB

    return true;
}
#endif

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
bool fossil_hostsys_get(fossil_hostsystem_t *info) {
    bool result = false;

    #ifdef _WIN32
        result = fossil_hostsys_get_windows(info);
    #elif __linux__
        result = fossil_hostsys_get_linux(info);
    #elif __APPLE__
        result = fossil_hostsys_get_macos(info);
    #else
        fprintf(stderr, "Unsupported platform\n");
    #endif

    if (result) {
        return fossil_hostsys_get_endian(info);
    } else {
        return false;
    }
}

/**
 * @brief Returns a string indicating the endianness of the system.
 * 
 * This function checks the endianness of the system and returns a string indicating
 * whether the system is big endian or little endian.
 * 
 * @param info Pointer to the fossil_hostsystem_t structure containing the system information.
 * @return Returns a string "Big Endian" if the system is big endian, otherwise "Little Endian".
 */
const char* fossil_hostsys_endian(fossil_hostsystem_t *info) {
    if (info->is_big_endian) {
        return "Big Endian";
    } else {
        return "Little Endian";
    }
}

/**
 * @brief Prints the system information to the standard output.
 * 
 * This function prints the retrieved system information to the standard output,
 * including the operating system name, version, CPU model, number of CPU cores,
 * total memory, free memory, and endianness.
 * 
 * @param info Pointer to the fossil_hostsystem_t structure containing the system information.
 */
void fossil_hostsys_print(fossil_hostsystem_t *info) {
    printf("Operating System: %s %s\n", info->os_name, info->os_version);
    printf("CPU: %s\n", info->cpu_model);
    printf("Number of Cores: %d\n", info->cpu_cores);
    printf("Total Memory: %d MB\n", (int)info->total_memory);
    printf("Free Memory: %d MB\n", (int)info->free_memory);
    printf("Endian: %s\n", fossil_hostsys_endian(info));
}
