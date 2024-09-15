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
#include <stdio.h>
#include <string.h>

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
    #include <mach/mach.h>
#endif

static bool fossil_hostsys_get_endian(fossil_hostsystem_t *info) {
    unsigned int num = 1;
    char *endian_check = (char*)&num;

    info->is_big_endian = (*endian_check == 0);
    return true;
}

#ifdef _WIN32
static bool fossil_hostsys_get_windows(fossil_hostsystem_t *info) {
    OSVERSIONINFOEX osvi;
    SYSTEM_INFO si;
    MEMORYSTATUSEX memInfo;

    memset(info, 0, sizeof(fossil_hostsystem_t));
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    if (!GetVersionEx((OSVERSIONINFO*)&osvi)) {
        fprintf(stderr, "Error getting Windows version information\n");
        return false;
    }

    strncpy(info->os_name, "Windows", sizeof(info->os_name));
    snprintf(info->os_version, sizeof(info->os_version), "%ld.%ld",
             osvi.dwMajorVersion, osvi.dwMinorVersion);

    GetNativeSystemInfo(&si);
    snprintf(info->cpu_model, sizeof(info->cpu_model), "Intel"); // Replace with actual model if available

    info->cpu_cores = si.dwNumberOfProcessors;

    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
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
                    strncpy(info->cpu_model, pos + 2, sizeof(info->cpu_model) - 1);
                    info->cpu_model[sizeof(info->cpu_model) - 1] = '\0'; // Ensure null-termination
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
    kern_return_t kr = host_statistics(host_port, HOST_VM_INFO, (host_info_t)&vm_stats, &count);
    
    if (kr != KERN_SUCCESS) {
        fprintf(stderr, "Error getting free memory information using mach API\n");
        return false;
    }
    info->free_memory = (vm_stats.free_count * vm_page_size) / (1024 * 1024); // Convert to MB

    return true;
}
#endif

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

const char* fossil_hostsys_endian(fossil_hostsystem_t *info) {
    return info->is_big_endian ? "Big Endian" : "Little Endian";
}

void fossil_hostsys_print(fossil_hostsystem_t *info) {
    printf("Operating System: %s\n", info->os_name);
    printf("Version: %s\n", info->os_version);
    printf("CPU Model: %s\n", info->cpu_model);
    printf("CPU Cores: %d\n", info->cpu_cores);
    printf("Total Memory: %ld MB\n", info->total_memory);
    printf("Free Memory: %ld MB\n", info->free_memory);
    printf("Endianness: %s\n", fossil_hostsys_endian(info));
}
