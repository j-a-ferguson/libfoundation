#ifndef SORTING_HPP_
#define SORTING_HPP_

#include <algorithm>
#include <iterator>

namespace Foundation {
    namespace Sorting {
        
        //{{{ col: type definitions
        template <typename Iterator>
        using ValueType = typename std::iterator_traits<Iterator>::value_type;

        template<typename Iterator> 
        using DiffType = typename std::iterator_traits<Iterator>::difference_type;
        //}}}
        

        //{{{ fun: insertion sort
        template <typename BidirIt> 
        requires std::bidirectional_iterator<BidirIt>
        void insertionSort(BidirIt start, BidirIt end) {
                        
            using Value = ValueType<BidirIt>;
            
            for(auto it1 = std::next(start); it1 != end; ++it1) {
                Value key = *it1;
                auto it2 = std::prev(it1);
                while (it2 != start && ((*it2) > key)) {
                    *it2 = *it1;
                    --it2;
                }
                *(std::next(it2)) = key; 

            }
        }
        //}}}

        


    }
}



#endif // SORTING_HPP_