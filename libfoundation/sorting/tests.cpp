#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fmt/core.h>
#include <gtest/gtest.h>
#include <libfoundation/sorting/sorting.hpp>
#include <list>

TEST(sorting, insertionSort)
{
    std::vector<int> integers(100);
    std::generate(integers.begin(), integers.end(), std::rand);

    foundation::sorting::insertionSort(integers.begin(), integers.end());
    ASSERT_TRUE(std::is_sorted(integers.begin(), integers.end()));
}