/**
 * @file type.hpp
 * @author Owen Cochell (owencochell@gmail.com)
 * @brief Various types used across snalib
 * @version 0.1
 * @date 2026-02-07
 *
 * @copyright Copyright (c) 2026
 *
 * Various types used across snalib.
 * Most of these are numerical,
 * and we provide some basic requirements each type should have.
 */

#pragma once

#include <arch/stddef.hpp>

namespace slb {

/// Unsigned 64bit integer type
/// to be used for ALL size operations
using size_t = arch::size_t;

}  // namespace slb
