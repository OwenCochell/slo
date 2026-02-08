/**
 * @file memory.hpp
 * @author Owen Cochell (owencochell@gmail.com)
 * @brief Memory components
 * @version 0.1
 * @date 2026-02-07
 *
 * @copyright Copyright (c) 2026
 *
 * This file contains components and definitions
 * for various memory components.
 * Because SLO needs to run on a variety of different devices
 * with a variety of different memory methods,
 * we need some generic components to standardize memory operations.
 *
 * The core idea is memory function definitions will be linked in depending
 * on the board we are compiling to.
 */

#pragma once

#include "type.hpp"

namespace slb::mem {

void* malloc(slb::size_t size);

void* calloc(slb::size_t size);

void free(void* ptr);

}  // namespace slb::mem
