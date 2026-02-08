/**
 * @file array.cpp
 * @author Owen Cochell (owencochell@gmail.com)
 * @brief Tests for array components
 * @version 0.1
 * @date 2026-02-07
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "snalib/array.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Array Class", "Test for array class") {

    // Define some sizes we will be testing

    constexpr int size_1 = 1;
    constexpr int size_10 = 10;
    constexpr int size_50 = 50;

    SECTION("Size", "Ensures we can create arrays of size") {

        // Just choose some arbitrary sizes...

        slb::arr::array<int, size_1> arr1;
        slb::arr::array<int, size_10> arr2;
        slb::arr::array<int, size_50> arr3;

        REQUIRE(arr1.size() == size_1);
        REQUIRE(arr2.size() == size_10);
        REQUIRE(arr3.size() == size_50);
    }

    SECTION("Set/Get", "Ensures we can set and get values") {

        slb::arr::array<int, size_10> arr;

        // Iterate over each index

        for (int i = 0; i < size_10; ++i) {

            // Set the value at this index

            arr.at(i) = i;

            // Ensures the value is correct

            REQUIRE(arr.at(i) == i);
        }
    }

    SECTION("Set/Get operator", "Ensures we can set and get values via []") {

        slb::arr::array<int, size_10> arr;

        // Iterate over each index

        for (int i = 0; i < size_10; ++i) {

            // Set the value at this index

            arr[i] = i;

            // Ensures the value is correct

            REQUIRE(arr[i] == i);
        }
    }

    SECTION("Default Construct", "Ensures we can default construct the array") {

        slb::arr::array<int, 10> arr;
    }

    SECTION("Value Construct", "Ensures we can construct with default values") {

        slb::arr::array<int, size_1> arr(1);

        REQUIRE(arr.at(0) == 1);
    }

    SECTION("Value Construct Many",
            "Ensures we can construct with many default values") {

        slb::arr::array<int, size_10> arr(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

        // Iterate over each value and ensure it's correct

        for (int i = 0; i < size_10; ++i) {
            REQUIRE(arr.at(i) == i);
        }
    }
}
