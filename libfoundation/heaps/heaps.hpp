#ifndef HEAPS_HPP_
#define HEAPS_HPP_

#include <__iterator/concepts.h>

#include <algorithm>
#include <iterator>

namespace Foundation
{
namespace Heaps
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
 * @param i Index at which t
 * @return requires
 */
template <typename BidirIt>
    requires std::bidirectional_iterator<BidirIt>
void maxHeapify(BidirIt begin, DiffType<BidirIt> heap_size, DiffType<BidirIt> i)
{
    using Diff  = DiffType<BidirIt>;

    auto i_iter = std::next(begin, i);

    while (true)
    {
        Diff l            = left<BidirIt>(i);
        Diff r            = right<BidirIt>(i);

        auto l_iter       = std::next(i_iter, l - i);
        auto r_iter       = std::next(l_iter, 1);
        auto largest_iter = i_iter;

        if ((l < heap_size) && (*l_iter > *largest_iter))
        {
            largest_iter = l_iter;
        }

        if ((r < heap_size) && (*r_iter > *largest_iter))
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
void buidMaxHeap(BidirIt begin, BidirIt end)
}  // namespace Heaps
}  // namespace Foundation

#endif  // HEAPS_HPP_