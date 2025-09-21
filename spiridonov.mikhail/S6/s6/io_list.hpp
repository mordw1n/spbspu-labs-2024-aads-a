#ifndef IO_LIST_HPP
#define IO_LIST_HPP

#include <iostream>

namespace spiridonov
{
  template < typename Container >
  void print(const Container& list, std::ostream& ostream)
  {
    bool is_first = true;
    for (auto&& i: list)
    {
      if (!is_first)
      {
        ostream << ' ';
      }
      is_first = false;
      ostream << i;
    }
    ostream << '\n';
  }
}

#endif
