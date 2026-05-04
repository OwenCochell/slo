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

#include <tenio/backend.hpp>

namespace arduino::gpio {

class ArdDigitalBackend : public tio::back::DigitalBackend {};

class ArdAnalogueBackend : public tio::back::AnalogueBackend {};

}  // namespace arduino::gpio
