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

#include <cstddef>
#include <cstdint>
#include <cstdlib>

namespace arch {

/// We use the C++ standard library for all these types

using size_t = std::size_t;
using uint32_t = std::uint32_t;
using int32_t = std::int32_t;
using uint16_t = std::uint16_t;
using int16_t = std::int16_t;
using uint8_t = std::uint8_t;
using int8_t = std::int8_t;

} // namespace arch
