/**
 * @file meta.hpp
 * @author Owen Cochell (owencochell@gmail.com)
 * @brief Various metaprogramming utilities
 * @version 0.1
 * @date 2026-05-05
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

namespace slb {

/**
 * @brief A binary decision between two types
 *
 * We choose between two types based upon a boolean.
 * If true is provided, then we will choose the first type.
 * If false is provided, then we will choose the second type.
 *
 * You can access the choosen type under the 'type' attribute.
 *
 * @tparam flag Boolean to decide which type to use
 * @tparam T Type selected if true
 * @tparam F Type selected if false
 */
template <bool flag, typename T, typename F>
struct choose_type;

template <typename T, typename F>
struct choose_type<true, T, F> {

    using type = T;
};

template <typename T, typename F>
struct choose_type<false, T, F> {

    using type = F;
};

/**
 * @brief A convenient alias for choose_type
 *
 * We automatically access the 'type' attribute of choose_type,
 * which is the type that was choosen based on the provided boolean.
 *
 * @tparam flag Boolean to decide which type to use
 * @tparam T Type selected if true
 * @tparam F Type selected if false
 */
template <bool flag, typename T, typename F>
using choose_type_t = choose_type<flag, T, F>::type;

}  // namespace slb
