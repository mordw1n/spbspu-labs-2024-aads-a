#ifndef INSERTION_SORT_HPP
#define INSERTION_SORT_HPP

#include <utility>
#include <iterator>
#include <algorithm>

namespace spiridonov
{
  template < typename BiDIterator, typename Compare >
  void insertionSort(BiDIterator first, BiDIterator last, Compare compare)
  {
    using category = typename std::iterator_traits< BiDIterator >::iterator_category;
    static_assert(std::is_base_of< std::bidirectional_iterator_tag, category >::value, "This algorithm requires bidirectional iterators");

    if (first == last)
    {
      return;
    }
    for (BiDIterator i = std::next(first); i != last; ++i)
    {
      for (BiDIterator j = i; j != first && compare(*j, *std::prev(j)); --j)
      {
        std::iter_swap(j, std::prev(j));
      }
    }
  }

  template < typename BiDIterator >
  void insertionSort(BiDIterator first, BiDIterator last)
  {
    insertionSort(first, last, std::less< typename std::iterator_traits< BiDIterator >::value_type >());
  }
}

#endif
