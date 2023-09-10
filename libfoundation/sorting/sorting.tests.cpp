// ------------------------------------------------------
//  John Alexander Ferguson, 2023
//  Distributed under CC0 1.0 Universal licence
// ------------------------------------------------------

#include "gtest/gtest.h"
#include <fmt/color.h>
#include <fmt/core.h>
#include <gtest/gtest.h>
#include <libfoundation/sorting/sorting.hpp>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <list>


namespace foundation
{
namespace sorting 
{

template <typename List>
class SortingTest : ::testing::Test
{
    protected: 

    List list0_;
    List list1_;
    List list2_;
    List list3_;
    List list4_;
    List list5_;
    List list6_;
    List list7_;
    List list8_;
    List list9_;
    List list10_;
    List list100_;
    List list1000_;
    List list10000_;


    void SetUp() override
    {
        list1_ = {0};
        list2_ = {5, 4};
    }
};

TYPED_TEST_SUITE_P(SortingTest);

// {{{ col: insertion sort tests
TEST(sorting, insertionSort0)
{
    std::vector<int> empty_array;
    insertionSort(empty_array.begin(), empty_array.end());
    ASSERT_TRUE(empty_array.empty());
}

TEST(sorting, insertionSort1)
{
    std::vector<int> len1_array = {4};
    insertionSort(len1_array.begin(), len1_array.end());
    ASSERT_EQ(len1_array.size(), 1);
    ASSERT_EQ(len1_array[0], 4);
}

TEST(sorting, insertionSort2)
{
    std::vector<int> array1 = {4, 5};
    insertionSort(array1.begin(), array1.end());
    ASSERT_EQ(array1.size(), 2);
    ASSERT_EQ(array1[0], 4);
    ASSERT_EQ(array1[1], 5);

    std::vector<int> array2 = {5, 4};
    insertionSort(array2.begin(), array2.end());
    ASSERT_EQ(array2.size(), 2);
    ASSERT_EQ(array2[0], 4);
    ASSERT_EQ(array2[1], 5);
}

TEST(sorting, insertionSort100)
{
    std::vector<int> integers(100);
    std::generate(integers.begin(), integers.end(), std::rand);

    insertionSort(integers.begin(), integers.end());
    ASSERT_TRUE(std::is_sorted(integers.begin(), integers.end()));
}
// }}}
// {{{ col: heap sort tests
TEST(sorting, heapSort)
{
    std::vector<int> integers(100);
    std::generate(integers.begin(), integers.end(), std::rand);

    heapSort(integers.begin(), integers.end());
    ASSERT_TRUE(std::is_sorted(integers.begin(), integers.end()));
}
// }}}
// {{{ col: quick sort tests
TEST(sorting, partition1)
{
    std::vector<int> input;
    internal::partition(input.begin(), input.end());
    ASSERT_TRUE(input.empty());
}

TEST(sorting, partition2)
{
    std::vector<int> input{1};
    internal::partition(input.begin(), input.end());

    ASSERT_EQ(input.size(), 1);
    ASSERT_EQ(input[0], 1);
}

TEST(sorting, partition3)
{
    std::vector<int> input{1, 2};
    internal::partition(input.begin(), input.end());

    ASSERT_EQ(input.size(), 2);
    ASSERT_EQ(input[0], 1);
    ASSERT_EQ(input[1], 2);
}

TEST(sorting, partition4)
{
    std::vector<int> input{2, 1};
    internal::partition(input.begin(), input.end());

    ASSERT_EQ(input.size(), 2);
    ASSERT_EQ(input[0], 1);
    ASSERT_EQ(input[1], 2);
}

TEST(sorting, partition5)
{
    std::vector<int> input{2, 8, 7, 1, 3, 5, 6, 4};
    std::vector<int> desired_output{2, 1, 3, 4, 7, 5, 6, 8};

    internal::partition(input.begin(), input.end());

    for (int i = 0; i < input.size(); ++i)
    {
        ASSERT_EQ(input[i], desired_output[i]);
    }
}

TEST(sorting, partition6)
{
    std::vector<int> input{3, 2, 1, -1, -2, -3, 0};
    std::vector<int> desired_output{-1, -2, -3, 0, 2, 1, 3};

    internal::partition(input.begin(), input.end());

    for (int i = 0; i < input.size(); ++i)
    {
        ASSERT_EQ(input[i], desired_output[i]);
    }
}

bool isPartition(const std::vector<int>& array, int pivot)
{
    bool is_partition{true};
    for (int i = 0; (i < pivot) && is_partition; ++i)
    {
        is_partition = is_partition && (array[i] <= array[pivot]);
    }

    for (int i = pivot + 1; i < array.size() && is_partition; ++i)
    {
        is_partition = is_partition && (array[i] > array[pivot]);
    }

    return is_partition;
}

TEST(sorting, partition7)
{
    std::vector<int> integers(100);
    std::generate(integers.begin(), integers.end(), std::rand);

    auto it = internal::partition(integers.begin(),
                                                       integers.end());

    int  idx = (it - integers.begin());
    ASSERT_TRUE(isPartition(integers, idx));
}

TEST(sorting, quickSort)
{
    std::vector<int> integers(100);
    std::generate(integers.begin(), integers.end(), std::rand);

    std::vector<int> integers2{integers};

    quickSort(integers.begin(), integers.end());
    std::sort(integers2.begin(), integers2.end());

    ASSERT_TRUE(std::is_sorted(integers.begin(), integers.end()));
}
//}}}
}
}