/**
 * @file backend.hpp
 * @author Owen Cochell (owencochell@gmail.com)
 * @brief GPIO backend interface definitions
 * @version 0.1
 * @date 2026-05-02
 *
 * @copyright Copyright (c) 2026
 *
 * This file defines a Tentacle IO backend for Arduino GPIO operations.
 */

#pragma once

#include <Arduino.h>

#include <tenio/backend.hpp>

namespace arduino::gpio {

class ArdDigitalBackend : public tio::back::DigitalBackend {
public:
    static bool dread(slb::size_t pnum) { return digitalRead(pnum) != 0; }

    static void dwrite(slb::size_t pnum, bool value) {
        digitalWrite(pnum, value ? HIGH : LOW);
    }
};

class ArdAnalogueBackend : public tio::back::AnalogueBackend<int> {
public:
    static ValueType aread(slb::size_t pnum) { return analogRead(pnum); }

    static void awrite(slb::size_t pnum, ValueType val) {
        analogWrite(pnum, val);
    }
};

}  // namespace arduino::gpio
