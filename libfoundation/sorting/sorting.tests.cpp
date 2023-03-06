#include <fmt/color.h>
#include <fmt/core.h>
#include <gtest/gtest.h>
#include <libfoundation/sorting/sorting.hpp>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <list>

// {{{ col: insertion sort tests
TEST(sorting, insertionSort)
{
    std::vector<int> integers(100);
    std::generate(integers.begin(), integers.end(), std::rand);

    foundation::sorting::insertionSort(integers.begin(), integers.end());
    ASSERT_TRUE(std::is_sorted(integers.begin(), integers.end()));
}
// }}}
// {{{ col: heap sort tests
TEST(sorting, heapSort)
{
    std::vector<int> integers(100);
    std::generate(integers.begin(), integers.end(), std::rand);

    foundation::sorting::heapSort(integers.begin(), integers.end());
    ASSERT_TRUE(std::is_sorted(integers.begin(), integers.end()));
}
// }}}
// {{{ col: quick sort tests
TEST(sorting, partition1)
{
    std::vector<int> input;
    foundation::sorting::internal::partition(input.begin(), input.end());
    ASSERT_TRUE(input.empty());
}

TEST(sorting, partition2)
{
    std::vector<int> input{1};
    foundation::sorting::internal::partition(input.begin(), input.end());

    ASSERT_EQ(input.size(), 1);
    ASSERT_EQ(input[0], 1);
}

TEST(sorting, partition3)
{
    std::vector<int> input{1, 2};
    foundation::sorting::internal::partition(input.begin(), input.end());

    ASSERT_EQ(input.size(), 2);
    ASSERT_EQ(input[0], 1);
    ASSERT_EQ(input[1], 2);
}

TEST(sorting, partition4)
{
    std::vector<int> input{2, 1};
    foundation::sorting::internal::partition(input.begin(), input.end());

    ASSERT_EQ(input.size(), 2);
    ASSERT_EQ(input[0], 1);
    ASSERT_EQ(input[1], 2);
}

TEST(sorting, partition5)
{
    std::vector<int> input{2, 8, 7, 1, 3, 5, 6, 4};
    std::vector<int> desired_output{2, 1, 3, 4, 7, 5, 6, 8};

    foundation::sorting::internal::partition(input.begin(), input.end());

    for (int i = 0; i < input.size(); ++i)
    {
        ASSERT_EQ(input[i], desired_output[i]);
    }
}

TEST(sorting, partition6)
{
    std::vector<int> input{3, 2, 1, -1, -2, -3, 0};
    std::vector<int> desired_output{-1, -2, -3, 0, 2, 1, 3};

    foundation::sorting::internal::partition(input.begin(), input.end());

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

    auto it = foundation::sorting::internal::partition(integers.begin(),
                                                       integers.end());

    int  idx = (it - integers.begin());
    ASSERT_TRUE(isPartition(integers, idx));
}

TEST(sorting, quickSort)
{
    std::vector<int> integers(100);
    std::generate(integers.begin(), integers.end(), std::rand);

    std::vector<int> integers2{integers};

    foundation::sorting::quickSort(integers.begin(), integers.end());
    std::sort(integers2.begin(), integers2.end());

    ASSERT_TRUE(std::is_sorted(integers.begin(), integers.end()));
}
//}}}
