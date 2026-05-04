/**
 * @file backend.hpp
 * @author Owen Cochell (owencochell@gmail.com)
 * @brief Definitions for the backend interface
 * @version 0.1
 * @date 2026-05-02
 *
 * @copyright Copyright (c) 2026
 *
 * A backend is a collection of functions that allow for interfacing with the
 * hardware. This is where the actual implementation of the pin operations will
 * be defined, and the abstraction layer will call these functions to perform
 * the necessary operations.
 */

#pragma once

#include <snalib/type.hpp>

namespace tio::back {

class DigitalBackend {
private:
public:
    bool dread(slb::size_t pnum) { return false; };

    void dwrite(slb::size_t pnum, bool val) {};
};

class AnalogueBackend {
private:
public:
    /// Numerical type for analogue values
    /// Should be wide enough to hold the maximum resolution of the analogue pin
    using ValueType = uint32_t;

    ValueType aread(slb::size_t pnum) { return 0; }

    void awrite(slb::size_t pnum, ValueType val) {};
};

}  // namespace tio::back
