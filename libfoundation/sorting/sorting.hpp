#ifndef SORTING_HPP_
#define SORTING_HPP_

#include <libfoundation/heaps/heaps.hpp>

#include <algorithm>
#include <iterator>
#include <stack>
#include <utility>

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
    using Diff  = DiffType<BidirIt>;

    /* doc
    After this call, all nodes are max-heaps, largest value in the
    array is located at first.
    */
    heaps::makeHeap(first, last);
    /* doc
    Initially the heap size and the length coincide
    */
    Diff    len{std::distance(first, last)};
    Diff    heap_size{len};
    BidirIt top = std::prev(last);

    for (Diff i = 0; i < len - 1; ++i)
    {
        /* doc
        Swap the maximum value with the end value, this now means the
        first element is no longer a max-heap and neither is the parent of
        the last element. To fix this, first the heap size is reduced to that
        the last element is not longer in the heap and second the first element
        is heapified
        */
        std::iter_swap(first, top);
        --heap_size;
        heaps::internal::heapify(first, heap_size, 0);
        std::advance(top, -1);
    }
}

//}}}

//{{{{ fun: quicksort
namespace internal
{

template <typename BidirIt>
    requires std::bidirectional_iterator<BidirIt>
BidirIt partition(BidirIt start, BidirIt end)
{
    using Value = ValueType<BidirIt>;
    using Diff  = DiffType<BidirIt>;
    Diff l      = std::distance(start, end);
    auto i_iter{std::prev(start)};

    if (l > 0)
    {
        Value pivot{*std::prev(end)};
        Diff  i{-1};
        auto  j_iter{start};

        for (Diff j = 0; j < l - 1; ++j)
        {
            auto xj{*j_iter};

            if (xj <= pivot)
            {
                ++i;
                std::advance(i_iter, 1);
                std::iter_swap(i_iter, j_iter);
            }
            std::advance(j_iter, 1);
        }
        std::iter_swap(std::next(i_iter), std::prev(end));
        std::advance(i_iter, 1);
    }
    return i_iter;
}

}  // namespace internal
template <typename BidirIt>
    requires std::bidirectional_iterator<BidirIt>
void quickSort(BidirIt start, BidirIt end)
{
    using Value = ValueType<BidirIt>;
    using Diff  = DiffType<BidirIt>;
    using Range = std::pair<BidirIt, BidirIt>;

    std::stack<Range> ranges;
    ranges.push({start, end});

    while (!ranges.empty())
    {
        Range current_range = ranges.top();
        ranges.pop();

        auto current_start = current_range.first;
        auto current_end   = current_range.second;
        auto pivot         = internal::partition(current_start, current_end);

        if (std::distance(current_start, pivot) > 1)
        {
            ranges.push({current_start, pivot});
        }

        auto tmp = std::next(pivot);
        if (std::distance(tmp, current_end) > 1)
        {
            ranges.push({tmp, current_end});
        }
    }
}

//}}}}
}  // namespace sorting
}  // namespace foundation

#endif  // SORTING_HPP_