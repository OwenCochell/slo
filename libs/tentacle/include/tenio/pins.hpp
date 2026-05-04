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
 * so to alleviate this we provide an abstraction that will standardize pin
 * and their operations.
 */

#pragma once

#include <snalib/array.hpp>
#include <snalib/type.hpp>

namespace tio::pin {

/**
 * @brief Determines the type of the pin
 *
 * This determines what features are enabled for this pin.
 * For example, a VOLT pin will only support outputting a constant
 * voltage, while a GPIO pin will support digital I/O operations.
 *
 */
enum class PinType : uint8_t {

    NONE,  // Pin has unsupported features
    VOLT,  // Pin emits constant voltage output
    GRND,  // Ground pin
    GPIO,  // GPIO pin (see modes for feature support)
};

/**
 * @brief Determines the mode of the pin
 *
 * This determines how the pin should be utilized. For example, an INPUT pin
 * will only support reading, while an OUTPUT pin will only support writing.
 * If a pin supports any of these operations,
 * then you can assume it is a GPIO pin, and the corresponding functions will be
 * available.
 *
 */
enum class PinMode : uint8_t {

    NONE,  // Pin does not support input or output

    ///
    // Supported I/O modes
    ///

    INPUT,   // Supports input
    OUTPUT,  // Supports output
    IO,      // Supports both input and output
};

enum class DigitalPinFeats : uint8_t {

    NONE,  // Pin only supports normal digital operations

    ///
    // Extra digital features
    ///

    PWM,    // Supports PWM
    PCM,    // Supports PCM
    CLOCK,  // Supports CLOCK
};

/**
 * @brief Concept that checks if the given pin mode supports writing
 *
 * @tparam M Pin mode to check
 */
template <PinMode M>
concept writeable = (M == PinMode::OUTPUT || M == PinMode::IO);

/**
 * @brief Concept that checks if the given pin mode supports reading
 *
 * @tparam M Pin mode to check
 */
template <PinMode M>
concept readable = (M == PinMode::INPUT || M == PinMode::IO);

class Pin {
private:
    /// Virtual number of this pin, to be used by abstraction layer
    slb::size_t num = 0;

    /// Physical pin number, to be used by backend
    slb::size_t pnum = 0;

    /// Type of pin, determines what is enabled
    PinType type = PinType::NONE;

public:
    constexpr Pin() = default;

    constexpr Pin(slb::size_t num, slb::size_t pnum, PinType type)
        : num(num), pnum(pnum), type(type) {}

    /**
     * @brief Gets the virtual number of this pin
     *
     * This is the number that should be used by the abstraction layer to refer
     * to this pin. The physical pin number can be accessed using get_pnum() and
     * should only be used by the backend.
     *
     * @return slb::size_t Virtual pin number
     */
    constexpr slb::size_t get_num() const { return num; }

    /**
     * @brief Gets the physical number of this pin
     *
     * This is the number that should be used by the backend to refer to this
     * pin. The virtual pin number can be accessed using get_num() and should be
     * used instead.
     *
     * @return slb::size_t Physical pin number
     */
    constexpr slb::size_t get_pnum() const { return pnum; }

    /**
     * @brief Gets the type of this pin
     *
     * This determines what features are enabled for this pin.
     * For example, a VOLT pin will only support outputting a constant
     * voltage, while a GPIO pin will support digital I/O operations.
     *
     * @return PinType Type of this pin
     */
    constexpr PinType get_type() const { return type; }
};

template <PinMode DM = PinMode::NONE>
class DigitalPin : public Pin {
private:
    /// Extra features of this digital pin, such as PWM or PCM support
    DigitalPinFeats feats = DigitalPinFeats::NONE;

public:
    constexpr DigitalPin() = default;

    constexpr DigitalPin(slb::size_t num, slb::size_t pnum)
        : Pin(num, pnum, PinType::GPIO) {}

    constexpr DigitalPinFeats dfeats() const { return feats; }

    /**
     * @brief Preforms a digital read on this pin
     *
     * This will read the current state of this pin.
     * Since this pin is digital, the value will be either true or false.
     * The pin must be in a mode that supports reading, otherwise this function
     * will not compile.
     *
     * @return true Pin current state is high
     * @return false Pin current state is low
     */
    bool dread() const
        requires readable<DM>;

    /**
     * @brief Preforms a digital write on this pin
     *
     * This will set the current state of this pin.
     * Since this pin is digital, the value must be either true or false.
     * The pin must be in a mode that supports writing, otherwise this function
     * will not compile.
     *
     * @param value New state for the pin, true for high, false for low
     */
    void dwrite(bool) const
        requires writeable<DM>;

    /**
     * @brief Supported I/O modes for this digital pin
     *
     * This is determined by the hardware capabilities of this pin, and may not
     * be changed at runtime. If a mode is not supported, the corresponding
     * read/write function will not compile.
     *
     * We need to differentiate between input and output modes for digital pins,
     * as some pins may only support one or the other.
     *
     * @return PinMode I/O modes supported by this pin
     */
    constexpr PinMode dmode() const { return DM; }
};

template <PinMode AM = PinMode::NONE, PinMode DM = PinMode::NONE>
class AnaloguePin : public DigitalPin<DM> {
private:
    /// Current mode of this analogue pin
    PinMode mode = AM;

public:
    AnaloguePin() = default;

    AnaloguePin(slb::size_t num, slb::size_t pnum)
        : DigitalPin<DM>(num, pnum) {}

    uint32_t aread() const
        requires readable<AM>;

    void awrite(uint32_t) const
        requires writeable<AM>;

    /**
     * @brief Supported I/O modes for this analogue pin
     *
     * This is determined by the hardware capabilities of this pin, and may not
     * be changed at runtime. If a mode is not supported, the corresponding
     * read/write function will not compile.
     *
     * We need to differentiate between input and output modes for analogue
     * pins, as some pins may only support one or the other.
     *
     * @return PinMode I/O modes supported by this pin
     */
    constexpr PinMode samode() const { return AM; }

    /**
     * @brief Gets the current mode of this analogue pin
     *
     * This is the mode that this pin is currently operating in. This may be
     * changed at runtime.
     *
     * @return constexpr PinMode Current pin mode
     */
    constexpr PinMode amode() const { return mode; }
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

}  // namespace tio::pin
