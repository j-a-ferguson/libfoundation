#include <fmt/core.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <list>

#include <libfoundation/sorting/sorting.hpp>

TEST(sorting, insertionSort) {

  std::vector<int> integers(100);
  std::generate(integers.begin(), integers.end(), std::rand);

  Foundation::Sorting::insertionSort(integers.begin(), integers.end());
  ASSERT_TRUE(std::is_sorted(integers.begin(), integers.end()));
}