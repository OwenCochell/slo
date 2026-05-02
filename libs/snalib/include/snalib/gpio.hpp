/**
 * @file gpio.hpp
 * @author Owen Cochell (owencochell@gmail.com)
 * @brief An abstraction for accessing GPIO
 * @version 0.1
 * @date 2026-05-01
 * 
 * @copyright Copyright (c) 2026
 * 
 * General Purpose Input / Output (GPIO) is a mechanism
 * that allows for interfacing with arbitrary components using 'pins'.
 * Each platform has a different standard and layout for accessing these pins,
 * so to alleviate this we provide an abstraction that will standardize GPIO operations.
 */

#pragma once

#include <cstdint>
#include "snalib/type.hpp"
#include "snalib/array.hpp"

namespace slb::gpio {

enum PinType {

    VOLT,    // Pin emits constant voltage output
    GRND,    // Ground pin
    INPUT,   // Can be configured for input only
    OUTPUT,  // Can be configured for output only
    IO,      // Can be configured for both input and output
};

enum DigitalPinMode {

    NONE,  // Pin only supports normal digital operations

    ///
    // Extra digital features
    ///

    PWM,     // Supports PWM
    PCM,     // Supports PCM
    CLOCK,   // Supports CLOCK

};

class Pin {
private:

    /// Virtual number of this pin, to be used by abstraction layer
    slb::size_t num = 0;

    /// Physical pin number, to be used by backend
    slb::size_t pnum = 0;

    /// Type of pin, determines what is enabled
    PinType type;

};

class AnaloguePin : public Pin {
public:

    uint32_t read();

    void write(uint32_t);
};

class DigitalPin : public Pin {
public:

};

/**
 * @brief Represents a board of pins
 *
 * A 'board' is a collection of pins that all have certain actions.
 * We define a 'virtual' board maps to a physical board,
 * but does not necessarily have the same IDs.
 * Pins are guaranteed to start at ID zero and increment accordingly.
 * Additionally, boards have a fixed size at compile time,
 * meaning no new pins can be defined on a board at runtime. 
 * 
 * @tparam S 
 */
template <size_t S>
using Board = slb::arr::array<Pin, S>;

}  // namespace slb::gpio
