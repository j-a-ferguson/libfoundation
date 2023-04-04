#ifndef HEAPS_HPP_
#define HEAPS_HPP_

#include <algorithm>
#include <cstdio>
#include <iterator>

namespace foundation
{
namespace heaps
{

template <typename Iterator>
using ValueType = typename std::iterator_traits<Iterator>::value_type;

template <typename Iterator>
using DiffType = typename std::iterator_traits<Iterator>::difference_type;

namespace internal
{

/**
 * @brief Returns the parent index of ``i``, which is ``floor(i / 2)``
 *
 * @tparam Iterator Iterator of type LegacyBidirectionalIterator
 * @param i Index in a sequence
 * @return The index of the parent
 */
template <typename Iterator>
inline DiffType<Iterator> parent(DiffType<Iterator> i)
{
    return (i >> 1);
}

/**
 * @brief Returns the left child index of ``i``.
 *
 * @tparam Iterator of type LegacyBidirectionalIterator
 * @param i Index in a sequence
 * @return The index of the left child
 */
template <typename Iterator>
inline DiffType<Iterator> left(DiffType<Iterator> i)
{
    return (i << 1) | 1;
}

/**
 * @brief Returns the right child of ``i``
 *
 * @tparam Iterator
 * @param i
 * @return DiffType<Iterator>
 */
template <typename Iterator>
inline DiffType<Iterator> right(DiffType<Iterator> i)
{
    return (i + 1) << 1;
}

/**
 * @brief Max-heapifies a given range ``[begin, end)``
 *
 * Assumptions: Both the left and right children of ``i`` are
 *              max-heaps.
 *
 * @tparam BidirIt Iterator of type LegacyBidirectionalIterator
 * @param begin Start of range
 * @param heap_size Size of sequence, so ``std::distance(begin, end)``
 * @param i Index  
 * @return requires
 */
template <typename BidirIt>
    requires std::bidirectional_iterator<BidirIt>
void heapify(BidirIt begin, DiffType<BidirIt> heap_size, DiffType<BidirIt> i)
{
    using Diff = DiffType<BidirIt>;

    auto i_iter = std::next(begin, i);

    while (true)
    {
        Diff l            = left<BidirIt>(i);
        Diff r            = right<BidirIt>(i);
        std::printf("l - i = %d", l -i)
        auto l_iter       = std::next(i_iter, l - i);
        auto r_iter       = std::next(l_iter, 1);
        auto largest_iter = i_iter;

        if ((l < heap_size) && (*largest_iter < *l_iter))
        {
            largest_iter = l_iter;
        }

        if ((r < heap_size) && (*largest_iter < *r_iter))
        {
            largest_iter = r_iter;
        }

        if (largest_iter != i_iter)
        {
            std::iter_swap(i_iter, largest_iter);
            i_iter = largest_iter;
            i      = std::distance(begin, i_iter);
        }
        else
        {
            break;
        }
    }
}

}  // namespace internal

template <typename BidirIt>
    requires std::bidirectional_iterator<BidirIt> 
bool isHeap(BidirIt first, BidirIt last)
{
    using Diff = DiffType<BidirIt>;
    Diff heap_size{std::distance(first, last)};
    Diff heap_size_half{internal::parent<BidirIt>(heap_size)};
    bool is_heap{true};

    // if heap_size is odd all non-leaf nodes have 2 children
    bool all_two_children{(heap_size % 2) == 1};
    Diff lim = all_two_children ? heap_size_half : heap_size_half - 1;

    /* First, we shall look at all the non-leaf nodes which are guaranteed to
       have two children */
    auto i_iter = first;
    for (Diff i = 0; i < lim; ++i)
    {
        Diff l      = internal::left<BidirIt>(i);
        auto l_iter = std::next(i_iter, l - i);

        if (*i_iter < *l_iter)
        {
            is_heap = false;
            break;
        }

        Diff r      = internal::right<BidirIt>(i);
        auto r_iter = std::next(l_iter, 1);

        if (*i_iter < *r_iter)
        {
            is_heap = false;
            break;
        }

        std::advance(i_iter, 1);
    }

    /* Second we look at the non-leaf node which may have only one child
     */
    if (!all_two_children)
    {
        Diff i      = heap_size_half - 1;
        Diff l      = internal::left<BidirIt>(i);
        auto l_iter = std::next(i_iter, l - i);

        if (*i_iter < *l_iter)
        {
            is_heap = false;
        }

        Diff r = internal::right<BidirIt>(i);
        if (r < heap_size)
        {
            auto r_iter = std::next(l_iter, 1);
            if (*i_iter < *r_iter)
            {
                is_heap = false;
            }
        }
    }
    return is_heap;
}

/**
 * @brief Makes the range of values in range ``[start, end)`` a max-heap
 *
 * @tparam BidirIt Iteraotr of type LegacyBidirectionalIterator
 * @param begin Start of range
 * @param end On-past-end of range
 */
template <typename BidirIt>
    requires std::bidirectional_iterator<BidirIt>
void makeHeap(BidirIt begin, BidirIt end)
{
    using Diff     = DiffType<BidirIt>;
    Diff heap_size = std::distance(begin, end);

    Diff start{internal::parent<BidirIt>(heap_size)};

    for (Diff i = start; i >= 0; --i)
    {
        internal::heapify(begin, heap_size, i);
    }
}
}  // namespace heaps
}  // namespace foundation

#endif  // HEAPS_HPP_