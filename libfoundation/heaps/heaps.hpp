#ifndef HEAPS_HPP_
#define HEAPS_HPP_

#include <algorithm>
#include <iterator>

namespace Foundation  {
    namespace Heaps {

        template <typename Iterator>
        using ValueType = typename std::iterator_traits<Iterator>::value_type;

        template<typename Iterator> 
        using DiffType = typename std::iterator_traits<Iterator>::difference_type;
                

        /*! Implements floor(i/2) */
        template<typename Iterator> 
        inline DiffType<Iterator> parent(DiffType<Iterator> i) {
            return (i >> 1);    
        }    

        /*! Implements 2 * i + 1*/
        template<typename Iterator> 
        inline DiffType<Iterator> left(DiffType<Iterator> i) {
            return (i << 1) | 1;
        }

        /*! Implements 2 * i + 1*/
        template<typename Iterator> 
        inline DiffType<Iterator> right(DiffType<Iterator> i) {
            return (i + 1) << 1;
        }

        /*! Max-heapifies a range of elements in [begin, begin + heap_size) 
        */
        template <typename BidirIt> 
        requires std::bidirectional_iterator<BidirIt>
        void maxHeapify(BidirIt begin, 
                        DiffType<BidirIt> heap_size, 
                        DiffType<BidirIt> i) 
        {
            using Diff = DiffType<BidirIt>;
            
            auto i_iter = std::next(begin, i);

            while(true) {
                Diff l = left<BidirIt>(i);                                
                Diff r = right<BidirIt>(i);                                    
                
                auto l_iter = std::next(i_iter, l - i);
                auto r_iter = std::next(l_iter, 1);
                auto largest_iter = i_iter;

                if((l < heap_size) && (*l_iter > *largest_iter)) {
                    largest_iter = l_iter;
                }

                if((r < heap_size) && (*r_iter > *largest_iter)) {
                    largest_iter = r_iter;
                }

                if(largest_iter != i_iter) {
                    
                    std::iter_swap(i_iter, largest_iter);
                    i_iter = largest_iter;
                    i = std::distance(begin, i_iter);
                }
                else {
                    break;
                }
                
            }
        }
    }
    //}}}
}

#endif // HEAPS_HPP_