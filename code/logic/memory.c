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
#include "fossil/lib/memory.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

fossil_memory_t fossil_memory_alloc(size_t size) {
    if (size == 0) {
        fprintf(stderr, "Error: fossil_memory_alloc() - Cannot allocate zero bytes.\n");
        return NULL;
    }
    
    fossil_memory_t ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Error: fossil_memory_alloc() - Memory allocation failed.\n");
        return NULL;
    }
    return ptr;
}

fossil_memory_t fossil_memory_realloc(fossil_memory_t ptr, size_t size) {
    // realloc(ptr, size) is safe even if ptr is NULL
    fossil_memory_t new_ptr = realloc(ptr, size);

    if (!new_ptr && size > 0) {
        fprintf(stderr, "Error: fossil_memory_realloc() - Memory reallocation failed.\n");
        return NULL;
    }
    return new_ptr;
}

void fossil_memory_free(fossil_memory_t ptr) {
    free(ptr); // No need for NULL check, free() already handles NULL.
}

fossil_memory_t fossil_memory_copy(fossil_memory_t dest, const fossil_memory_t src, size_t size) {
    if (!dest || !src) {
        fprintf(stderr, "Error: fossil_memory_copy() - Source or destination is NULL.\n");
        return NULL;
    }

    if (size == 0) {
        fprintf(stderr, "Error: fossil_memory_copy() - Cannot copy zero bytes.\n");
        return NULL;
    }
    
    return memcpy(dest, src, size);
}

fossil_memory_t fossil_memory_set(fossil_memory_t ptr, int32_t value, size_t size) {
    if (!ptr) {
        fprintf(stderr, "Error: fossil_memory_set() - Pointer is NULL.\n");
        return NULL;
    }

    if (size == 0) {
        fprintf(stderr, "Error: fossil_memory_set() - Cannot set zero bytes.\n");
        return NULL;
    }
    
    return memset(ptr, value, size);
}

fossil_memory_t fossil_memory_dup(const fossil_memory_t src, size_t size) {
    if (!src || size == 0) {
        fprintf(stderr, "Error: fossil_memory_dup() - Invalid source or zero size.\n");
        return NULL;
    }

    fossil_memory_t dest = fossil_memory_alloc(size);
    if (!dest) {
        return NULL;  // Error already handled in fossil_memory_alloc
    }

    return memcpy(dest, src, size);
}

void fossil_memory_zero(fossil_memory_t ptr, size_t size) {
    if (!ptr || size == 0) {
        fprintf(stderr, "Error: fossil_memory_zero() - Invalid pointer or zero size.\n");
        return;
    }
    
    memset(ptr, 0, size);
}

fossil_memory_t fossil_memory_alloc_aligned(size_t size, size_t alignment) {
    if (size == 0 || alignment == 0 || (alignment & (alignment - 1)) != 0) {
        fprintf(stderr, "Error: fossil_memory_alloc_aligned() - Invalid size or alignment.\n");
        return NULL;
    }

    void* ptr;
    int result = posix_memalign(&ptr, alignment, size);  // POSIX
    if (result != 0) {
        fprintf(stderr, "Error: fossil_memory_alloc_aligned() - Memory alignment failed.\n");
        return NULL;
    }

    return ptr;
}

int fossil_memory_compare(const fossil_memory_t ptr1, const fossil_memory_t ptr2, size_t size) {
    if (!ptr1 || !ptr2 || size == 0) {
        fprintf(stderr, "Error: fossil_memory_compare() - Invalid pointers or zero size.\n");
        return -1;  // Return -1 for invalid input
    }

    return memcmp(ptr1, ptr2, size);
}

fossil_memory_t fossil_memory_move(fossil_memory_t dest, const fossil_memory_t src, size_t size) {
    if (!dest || !src || size == 0) {
        fprintf(stderr, "Error: fossil_memory_move() - Invalid source or destination pointers, or zero size.\n");
        return NULL;
    }

    return memmove(dest, src, size);
}

fossil_memory_t fossil_memory_resize(fossil_memory_t ptr, size_t old_size, size_t new_size) {
    if (new_size == 0) {
        fossil_memory_free(ptr);
        return NULL;
    }

    fossil_memory_t new_ptr = fossil_memory_realloc(ptr, new_size);
    if (!new_ptr) {
        fprintf(stderr, "Error: fossil_memory_resize() - Memory resize failed, old memory preserved.\n");
        return ptr;  // Return the old memory if realloc fails
    }

    return new_ptr;
}

bool fossil_memory_is_valid(const fossil_memory_t ptr) {
    if (!ptr) {
        return false;
    }
    // Optional: Add more validation logic if needed, but normally you'd rely on the caller to manage validity.
    return true;
}

void fossil_memory_debug(const fossil_memory_t ptr, size_t size) {
    if (!ptr || size == 0) {
        fprintf(stderr, "Error: fossil_memory_debug() - Invalid pointer or size.\n");
        return;
    }

    printf("Memory block at %p of size %zu bytes:\n", ptr, size);
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", ((unsigned char*)ptr)[i]);
        if (i % 16 == 15) {
            printf("\n");
        }
    }
    printf("\n");
}
