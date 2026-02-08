/**
 * @file array.hpp
 * @author Owen Cochell (owencochell@gmail.com)
 * @brief Array class
 * @version 0.1
 * @date 2026-02-07
 *
 * @copyright Copyright (c) 2026
 *
 * Contains components for working with fixed
 * size contiguous arrays.
 */

#pragma once

#include "type.hpp"

namespace slb::arr {

/**
 * @brief A container that stores contiguous fixed size data
 *
 * An 'array' is a contiguous fixed size sequence of data.
 * The size of this data is defined at compile time,
 * meaning once defined it can't be changed.
 *
 * This is a simple wrapper for a C style array,
 * but with extra added checks and modern C++ support.
 * This implies a few things, mainly that the space between elements
 * can be determined by preforming the difference between the memory location
 * of each element.
 * We also avoid some of the issues with C style arrays,
 * such as array to pointer decay.
 *
 * @tparam T Type of value to store
 * @tparam S Size of array
 */
template <typename T, size_t S>
    requires(S > 0)
class array {
private:
    /// Underlying array containing data
    T arr[S];

public:
    /// Type this array is storing
    using type = T;
    /// Reference type
    using reference = T&;
    /// Const reference type
    using const_reference = const T&;
    /// Type of internal size type
    using size_type = size_t;

    /// Default constructor
    constexpr array() = default;

    /**
     * @brief Constructs an array with the given values
     *
     * The number of provided values must be equal
     * to the number of elements in this array,
     * TODO: Add checks to confirm types
     *
     * @tparam A First type
     * @tparam As Second type
     */
    template <typename A, typename... As>
        requires(sizeof...(As) + 1 == S)
    constexpr array(A a1, As... an) : arr{a1, an...} {}

    /**
     * @brief Determines the size of this array
     *
     * @return constexpr size_t Number of elements in this array
     */
    constexpr size_t size() { return S; }

    /**
     * @brief Gets the value at the given index
     *
     * @param index Index of value to get
     * @return constexpr reference Value at index
     */
    constexpr reference at(size_t index) { return arr[index]; }

    /**
     * @brief Gets the value at the given index
     *
     * This is a constant read only method.
     *
     * @param index Index of value to get
     * @return constexpr reference Value at index
     */
    constexpr const_reference at(size_t index) const { return arr[index]; }

    /**
     * @brief Operator overload for getting value
     *
     * @param index Index of value to get
     * @return constexpr reference Value at index
     */
    constexpr reference operator[](size_t index) { return arr[index]; }

    /**
     * @brief Operator overload for getting const value
     *
     * @param index Index of value to get
     * @return constexpr const_reference  Value at index
     */
    constexpr const_reference operator[](size_t index) const {
        return arr[index];
    }
};

}  // namespace slb::arr
