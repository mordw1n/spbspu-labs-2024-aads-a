#ifndef CHECKING_SORTINGS_HPP
#define CHECKING_SORTINGS_HPP

#include <deque>
#include "../common/forwardList.hpp"
#include "../common/bidirectionalList.hpp"
#include "insertionSort.hpp"
#include "shellSort.hpp"
#include "quickSort.hpp"
#include "random.hpp"
#include "io_list.hpp"
#include "shellStrategies.hpp"

namespace spiridonov
{
  template < typename Container, typename Compare >
  void printCheckQuickSort(Container list, size_t size, Compare cmp, std::ostream& ostream)
  {
    spiridonov::quickSort(list.begin(), size, cmp);
    spiridonov::print(list, ostream);
  }

  template < typename Container, typename Compare >
  void printCheckInsertSort(Container list, Compare cmp, std::ostream& ostream)
  {
    spiridonov::insertionSort(list.begin(), list.end(), cmp);
    spiridonov::print(list, ostream);
  }

  template < typename Container, typename Compare >
  void printCheckShellSort(Container list, size_t size, Compare cmp, std::ostream& ostream)
  {
    spiridonov::shellSort(list.begin(), list.end(), cmp, spiridonov::HibbardStrategy(size));
    spiridonov::print(list, ostream);
  }
}

namespace spiridonov
{
  namespace detail
  {
    template < typename T >
    struct checkSortings
    {
      checkSortings() = delete;
      checkSortings(size_t size, std::ostream& ostream):
        size_(size),
        flist_(),
        blist_(),
        deq_()
      {
        for (auto i = size_t{0}; i < size_; ++i)
        {
          if (i != size_t{0})
          {
            ostream << ' ';
          }
          T value = spiridonov::generateRand< T >();
          ostream << value;
          flist_.pushBack(value);
          blist_.pushBack(value);
          deq_.push_back(value);
        }
        ostream << '\n';
      }
      ~checkSortings() = default;

      template < typename Compare >
      void printCheckSorts(Compare cmp, std::ostream& ostream)
      {
        printCheckQuickSort(flist_, size_, cmp, ostream);
        printCheckQuickSort(blist_, size_, cmp, ostream);
        printCheckQuickSort(deq_, size_, cmp, ostream);

        printCheckInsertSort(blist_, cmp, ostream);
        printCheckInsertSort(deq_, cmp, ostream);

        printCheckShellSort(deq_, size_, cmp, ostream);
      }

    private:
      size_t size_;
      spiridonov::ForwardList< T > flist_;
      spiridonov::BidirectionalList< T > blist_;
      std::deque< T > deq_;
    };
  }
}

#endif
