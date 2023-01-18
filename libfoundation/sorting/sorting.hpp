#ifndef SORTING_HPP_
#define SORTING_HPP_

#include <algorithm>
#include <iterator>
#include <libfoundation/heaps/heaps.hpp>

namespace foundation
{
namespace sorting
{

//{{{ col: type definitions
template <typename Iterator>
using ValueType = typename std::iterator_traits<Iterator>::value_type;

template <typename Iterator>
using DiffType = typename std::iterator_traits<Iterator>::difference_type;
//}}}

//{{{ fun: insertion sort
/**
 * @brief Sorts a given range using the insertion sort algorithm
 *
 * @tparam BidirIt Bidirectional Iterator type
 * @param start The beginning of the range
 * @param end The end of the range
 */
template <typename BidirIt>
    requires std::bidirectional_iterator<BidirIt>
void insertionSort(BidirIt start, BidirIt end)
{
    using Value = ValueType<BidirIt>;

    for (auto it1 = std::next(start); it1 != end; ++it1)
    {
        Value key = *it1;
        auto  it2 = std::prev(it1);
        while (it2 != start && ((*it2) > key))
        {
            *it2 = *it1;
            --it2;
        }
        *(std::next(it2)) = key;
    }
}
//}}}
///{{{ fun: heap sort
template <typename BidirIt>
    requires std::bidirectional_iterator<BidirIt>
void heapSort(BidirIt first, BidirIt last)
{
    using Value = ValueType<BidirIt>;
    using Diff = DiffType<BidirIt>;

    heaps::makeHeap(first, last);
    Diff heap_size{std::distance(first, last)};

    for(auto ) 
    {
        std::
    }
    
}

//}}}

}  // namespace sorting
}  // namespace foundation

#endif  // SORTING_HPP_