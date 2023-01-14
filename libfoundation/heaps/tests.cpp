#include <gtest/gtest.h>
#include <fmt/core.h>

#include <list>
#include <algorithm>
#include <cstdlib>
#include <cmath>

#include <libfoundation/heaps/heaps.hpp>


TEST(heaps, parent) {
    using Iter = std::list<int>::iterator;
    using Diff = Foundation::Heaps::DiffType<Iter>;

    for(Diff i = 0; i < 100; ++i) {
        int parent1 = Foundation::Heaps::parent<Iter>(i);
        int parent2 = i / 2;
        ASSERT_EQ(parent1, parent2);       
    }
}

TEST(heaps, left) {
    using Iter = std::list<int>::iterator;
    using Diff = Foundation::Heaps::DiffType<Iter>;

    for(Diff i = 0; i < 100; ++i) {
        int left1 = Foundation::Heaps::left<Iter> (i);
        int left2 = (2 * i) + 1;
        ASSERT_EQ(left1, left2);
    }
}

TEST(heaps, right) {
    using Iter = std::list<int>::iterator;
    using Diff = Foundation::Heaps::DiffType<Iter>;

    for(Diff i = 0; i < 100; ++i) {
        int right1 = Foundation::Heaps::right<Iter>(i);
        int right2 = 2 * (i + 1);
        ASSERT_EQ(right1, right2);
    }
}

TEST(heaps, maxHeapify) {
    using Iter = std::list<int>::iterator;
    using Diff = Foundation::Heaps::DiffType<Iter>;

    {
        std::vector<int> data1 = {3, 13, 14, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8};
        Foundation::Heaps::maxHeapify(data1.begin(), data1.size(), 0);
        std::vector<int> data2 = {14, 13, 12, 9, 10, 11, 8, 1, 2, 3, 4, 5, 6, 7, 3};    
        for(auto i = 0; i < data1.size(); ++i) {
            // std::printf("%d %d %d\n",i,  data1[i], data2[i]);
            ASSERT_EQ(data1[i], data2[i]);
        }
    }

    {
        std::vector<int> data1 = {3, 14, 13, 12, 11, 10, 9, 7, 8, 6, 5, 4, 3, 2, 1};
        Foundation::Heaps::maxHeapify(data1.begin(), data1.size(), 0);
        std::vector<int> data2 = {14, 12, 13, 8, 11, 10, 9, 7, 3, 6, 5, 4, 3, 2, 1};    
        for(auto i = 0; i < data1.size(); ++i) {
            ASSERT_EQ(data1[i], data2[i]);
        }
    }
}