/**
 * @file vector.hpp
 * @author Owen Cochell (owencochell@gmail.com)
 * @brief Vector class
 * @version 0.1
 * @date 2026-02-16
 *
 * @copyright Copyright (c) 2026
 *
 * Contains components for working with
 * dynamically allocated contiguous arrays.
 */

#pragma once

#include "memory.hpp"
#include "type.hpp"

namespace slb::vect {

template <typename T>
struct vector {
private:
    /// Pointer to contiguous data
    T* datap;

    /// Number of values in the vector
    size_t sizev = 0;

    /// Capacity of the vector
    size_t cap = 0;

    /**
     * @brief Resizes the underlying data
     *
     * We simply resize the underlying data pointer
     * to the capacity and report any errors we encounter.
     *
     */
    void mem_resize() {

        // Resize this vector to contain the capacity

        datap = realloc(datap, cap);

        // TODO: Add some error checking here?
    }

public:
    vector() = default;

    /**
     * @brief Vector destructor
     *
     * We ensure the memory we were managing is
     * properly freed.
     *
     */
    ~vector() { free(datap); }

    /**
     * @brief Gets the size of this vector
     *
     * The 'size' is the number of elements currently
     * present in this vector.
     * This is NOT the capacity,
     * which is the amount of 'spaces' available for entries.
     * Size will always be <= than the capacity.
     *
     * @return size_t Vector size
     */
    size_t size() const { return sizev; }

    /**
     * @brief Gets the capacity of this vector
     *
     * The 'capacity' is the number of elements this
     * vector could contain.
     * Just because a vector has space for elements
     * does not mean it contains anything!
     * 'Size' should be used for determining
     * the number of elements present.
     * The capacity will always be >= the size.
     *
     * @return size_t Vector capacity
     */
    size_t capacity() const { return cap; }

    /**
     * @brief Determines if this vector is empty
     *
     * A vector is empty when it contains no values.
     * Just because a vector is empty does not mean
     * it's capacity is zero!
     *
     * @return true Vector has no elements
     * @return false Vector has some elements
     */
    bool empty() const { return sizev == 0; }

    /**
     * @brief Increases the capacity of the vector
     *
     * We set the capcity to the provided value.
     * This will allocate all the necessary memory required
     * to match the new capacity.
     * This will allocate all the necessary memory in one shot,
     * instead of piecewise in smaller chunks.
     * This can greatly improve performance if you
     * know the number of elements the vector should contain ahead of time.
     *
     * If the new vector capacity is <= the current capacity,
     * then this operation does nothing.
     *
     * @param nsize New vector capacity
     */
    void reserve(size_t nsize) {

        // Determine if we already have enough space

        if (cap < nsize) {

            // Set the new capacity and reallocate

            cap = nsize;
            mem_resize();
        }
    }

    /**
     * @brief Reduces capacity to current size
     *
     * We will set our capacity to the current size,
     * which will deallocate any capacity that is currently unused.
     * This allows you to reclaim any memory not in use.
     *
     */
    void shrink_to_fit() {

        // Set the capacity to be equal to the size

        cap = sizev;

        // Reallocate the array,
        // should shrink to the new size

        mem_resize();
    }

    /**
     * @brief Clears all elements from this vector
     *
     *
     *
     */
    void clear() {

        // First, set the size and capacity to zero

        sizev = 0;
        cap = 0;

        // Free the data, to be reallocated in another operation

        free(datap);
    }
};

}  // namespace slb::vect
