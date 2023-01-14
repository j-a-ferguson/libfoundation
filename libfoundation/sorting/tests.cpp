#include <gtest/gtest.h>
#include <fmt/core.h>

#include <list>
#include <algorithm>
#include <cstdlib>
#include <cmath>

#include <libfoundation/sorting/sorting.hpp>

TEST(sorting, insertionSort) {

    std::vector<int> integers(100);
    std::generate(integers.begin(), integers.end(), std::rand);    
    
    Foundation::Sorting::insertionSort(integers.begin(), integers.end());    
    ASSERT_TRUE(std::is_sorted(integers.begin(), integers.end()));

}