#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <utility>
#include <iterator>

namespace
{
  template < typename FwdIterator, typename Compare >
  FwdIterator partition(FwdIterator first, FwdIterator prev_last, Compare compare)
  {
    for (FwdIterator left = first; left != prev_last; ++left)
    {
      if (compare(*left, *prev_last))
      {
        std::iter_swap(left, first++);
      }
    }
    std::iter_swap(first, prev_last);

    return first;
  }
}

namespace spiridonov
{
  template < typename FwdIterator, typename Compare >
  void quickSort(FwdIterator first, typename FwdIterator::difference_type size, Compare compare)
  {
    using category = typename std::iterator_traits< FwdIterator >::iterator_category;
    static_assert(std::is_base_of< std::forward_iterator_tag, category >::value, "This algorithm requires forward iterators");
    if (size < 1)
    {
      return;
    }
    FwdIterator pivot = ::partition(first, std::next(first, size - 1), compare);
    typename FwdIterator::difference_type new_size = std::distance(first, pivot);
    quickSort(first, new_size, compare);
    quickSort(std::next(pivot), size - new_size - 1, compare);
  }

  template < typename FwdIterator >
  void quickSort(FwdIterator first, typename FwdIterator::difference_type size)
  {
    quickSort(first, size, std::less< typename std::iterator_traits< FwdIterator >::value_type >());
  }
}

#endif