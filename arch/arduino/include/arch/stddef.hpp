/**
 * @file stddef.hpp
 * @author Owen Cochell (owencochell@gmail.com)
 * @brief Definitions for various types
 * @version 0.1
 * @date 2026-02-07
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <Arduino.h>

#include <stddef.h>
#include <stdint.h>

namespace arch {

/// We use the arduino versions of these types

using size_t = size_t;
using uint32_t = uint32_t;
using int32_t = int32_t;
using uint16_t = uint16_t;
using int16_t = int16_t;
using uint8_t = uint8_t;
using int8_t = int8_t;

}  // namespace arch
