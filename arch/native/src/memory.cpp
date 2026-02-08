/**
 * @file memory.cpp
 * @author Owen Cochell (owencochell@gmail.com)
 * @brief Implementations for memory operations
 * @version 0.1
 * @date 2026-02-07
 *
 * @copyright Copyright (c) 2026
 *
 * We offload ALL memory operations
 * to the C standard library.
 * These function definitions are mostly just aliases.
 */

#include <cstdlib>

namespace slb::memory {

/**
 * @brief Allocates size bytes of memory
 *
 * We simply defer this operation
 * to the C standard libary.
 *
 * @param size Number of bytes to allocate
 * @return void* Allocated data
 */
void* malloc(std::size_t size) { return ::malloc(size); }

/**
 * @brief Frees the allocated memory
 *
 * We simply defer this operation
 * to the C standard library.
 *
 * @param ptr Pointer to free
 */
void free(void* ptr) { ::free(ptr); }

}  // namespace slb::memory
