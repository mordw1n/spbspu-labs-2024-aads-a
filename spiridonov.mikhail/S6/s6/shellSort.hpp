#ifndef SHELL_SORT_HPP
#define SHELL_SORT_HPP

#include <utility>
#include <iterator>
#include "shellStrategies.hpp"

namespace spiridonov
{
  template < typename BiDIterator, typename Compare, typename Strategy >
  void shellSort(BiDIterator first, BiDIterator last, Compare compare, Strategy strategy)
  {
    using category = typename std::iterator_traits< BiDIterator >::iterator_category;
    static_assert(std::is_base_of< std::bidirectional_iterator_tag, category >::value, "This algorithm requires bidirectional iterators");

    if (first == last)
    {
      return;
    }

    using value_type = typename std::iterator_traits< BiDIterator >::difference_type;
    value_type h = 1;

    while (!strategy.isEnd())
    {
      for (BiDIterator i = std::next(first, h); i != last; ++i)
      {
        for (BiDIterator j = i; std::distance(first, j) >= h && compare(*j, *std::prev(j, h)); std::advance(j, -h))
        {
          std::iter_swap(j, std::prev(j, h));
        }
      }

      h = strategy();
    }
  }

  template < typename BiDIterator, typename Strategy >
  void shellSort(BiDIterator first, BiDIterator last, Strategy strategy)
  {
    shellSort(first, last, std::less< typename std::iterator_traits< BiDIterator >::value_type >(), strategy);
  }
}

#endif