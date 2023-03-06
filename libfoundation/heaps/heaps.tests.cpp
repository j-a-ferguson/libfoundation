#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <list>
#include <numeric>

#include <fmt/core.h>
#include <gtest/gtest.h>
#include <libfoundation/heaps/heaps.hpp>

namespace foundation
{
namespace heaps
{

TEST(heaps, parent)
{
    using Iter = std::list<int>::iterator;
    using Diff = foundation::heaps::DiffType<Iter>;

    for (Diff i = 0; i < 100; ++i)
    {
        int parent1 = foundation::heaps::internal::parent<Iter>(i);
        int parent2 = i / 2;
        ASSERT_EQ(parent1, parent2);
    }
}

TEST(heaps, left)
{
    using Iter = std::list<int>::iterator;
    using Diff = foundation::heaps::DiffType<Iter>;

    for (Diff i = 0; i < 100; ++i)
    {
        int left1 = foundation::heaps::internal::left<Iter>(i);
        int left2 = (2 * i) + 1;
        ASSERT_EQ(left1, left2);
    }
}

TEST(heaps, right)
{
    using Iter = std::list<int>::iterator;
    using Diff = foundation::heaps::DiffType<Iter>;

    for (Diff i = 0; i < 100; ++i)
    {
        int right1 = foundation::heaps::internal::right<Iter>(i);
        int right2 = 2 * (i + 1);
        ASSERT_EQ(right1, right2);
    }
}

TEST(heaps, heapify)
{
    using Iter = std::list<int>::iterator;
    using Diff = foundation::heaps::DiffType<Iter>;

    {
        std::vector<int> data1 = {3, 13, 14, 9, 10, 11, 12, 1,
                                  2, 3,  4,  5, 6,  7,  8};
        foundation::heaps::internal::heapify(data1.begin(), data1.size(), 0);
        std::vector<int> data2 = {14, 13, 12, 9, 10, 11, 8, 1,
                                  2,  3,  4,  5, 6,  7,  3};
        for (auto i = 0; i < data1.size(); ++i)
        {
            // std::printf("%d %d %d\n",i,  data1[i], data2[i]);
            ASSERT_EQ(data1[i], data2[i]);
        }
    }

    {
        std::vector<int> data1 = {3, 14, 13, 12, 11, 10, 9, 7,
                                  8, 6,  5,  4,  3,  2,  1};
        foundation::heaps::internal::heapify(data1.begin(), data1.size(), 0);
        std::vector<int> data2 = {14, 12, 13, 8, 11, 10, 9, 7,
                                  3,  6,  5,  4, 3,  2,  1};
        for (auto i = 0; i < data1.size(); ++i)
        {
            ASSERT_EQ(data1[i], data2[i]);
        }
    }
}

/**
 * @brief Verifies that ``isHeap()`` returns true for a sequence in
 *        in descending order.
 */
TEST(heaps, isHeap1)
{
    std::list<int> data(10);
    std::iota(data.begin(), data.end(), 0);
    std::reverse(data.begin(), data.end());
    bool is_heap = foundation::heaps::isHeap(data.begin(), data.end());
    ASSERT_TRUE(is_heap);
}

/**
 * @brief Verifies that ``isHeap()`` returns false for a sequence
 *        where a node which violates the heap property has only one child
 */
TEST(heaps, isHeap2)
{
    std::list<int> data(10);
    std::iota(data.begin(), data.end(), 0);
    std::reverse(data.begin(), data.end());
    std::iter_swap(std::next(data.begin(), 4), std::next(data.begin(), 9));
    bool is_heap = foundation::heaps::isHeap(data.begin(), data.end());
    ASSERT_FALSE(is_heap);
}

/**
 * @brief Verifies that ``isHeap()`` returns false for a sequence
 *        where a node which violates the heap property has only
 *         two children.
 */
TEST(heaps, isHeap3)
{
    {
        std::list<int> data(10);
        std::iota(data.begin(), data.end(), 0);
        std::reverse(data.begin(), data.end());
        std::iter_swap(std::next(data.begin(), 1), std::next(data.begin(), 3));
        bool is_heap = foundation::heaps::isHeap(data.begin(), data.end());
        ASSERT_FALSE(is_heap);
    }
}

/**
 * @brief Verify that the sorted array remains unchanged
 *
 */
TEST(heaps, makeHeap1)
{
    std::list<int> data(10);
    std::iota(data.begin(), data.end(), -5);
    std::reverse(data.begin(), data.end());
    foundation::heaps::makeHeap(data.begin(), data.end());

    int i{0};
    for (int val : data)
    {
        ASSERT_EQ(val, 4 - i);
        ++i;
    }
}

TEST(heaps, makeHeap2)
{
    std::list<int> data1 = {8, 10, 11, 2, 3, 15, 16, 1, 20};
    foundation::heaps::makeHeap(data1.begin(), data1.end());

    std::vector<int> data2 = {20, 10, 16, 8, 3, 15, 11, 1, 2};

    int              i{0};
    for (auto val : data1)
    {
        ASSERT_EQ(val, data2[i]);
        ++i;
    }
}

}  // namespace heaps
}  // namespace foundation