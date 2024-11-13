#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "forward_list.hpp"
#include <limits>
#include <algorithm>
#include <iostream>

namespace spiridonov
{
  using nameList = std::pair<std::string, List< size_t >>;

  nameList inputLine(std::istream& in)
  {
    nameList result;
    in >> result.first;
    if (result.first.empty())
    {
      throw std::invalid_argument("Name is empty");
    }

    size_t inNum = 0;

    while (in >> inNum)
    {
      result.second.push_back(inNum);
    }

    return result;
  }

  List<nameList> input(std::istream& in)
  {
    List<nameList> Lists;
    try
    {
      while (in)
      {
        Lists.push_back(inputLine(in));
        if (!in.eof())
        {
          in.clear();
        }
      }
    }
    catch (const std::invalid_argument&)
    {
      throw std::invalid_argument("Name is empty");
    }

    return Lists;
  }

  template <typename T>
  void printListValues(const List<T>& list)
  {
    for (auto it = list.begin(); it != list.end(); ++it)
    {
      std::cout << *it;
      if (it + 1 != list.end())
      {
        std::cout << " ";
      }
    }
    std::cout << '\n';
  }

  template <typename T>
  T sumListValues(const List<T>& list)
  {
    size_t max_ULL = std::numeric_limits<size_t>::max();

    T sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it)
    {
      sum += *it;
      if (max_ULL - sum <= *it)
      {
        throw std::overflow_error("Error: overflow");
      }
    }
    return sum;
  }
}

#endif
