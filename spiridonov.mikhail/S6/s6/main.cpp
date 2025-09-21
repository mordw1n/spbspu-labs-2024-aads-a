#include <iostream>
#include <iomanip>
#include "checkingSortings.hpp"

namespace
{
  template < typename T, typename Compare >
  void sortingLists(size_t count, Compare cmp, std::ostream& ostream)
  {
    spiridonov::detail::checkSortings< T > checker(count, ostream);
    checker.printCheckSorts(cmp, ostream);
  }

  bool isCorrectSortingName(const std::string& str)
  {
    return str == "ascending" || str == "descending";
  }
  bool isCorrectValueType(const std::string& str)
  {
    return str == "ints" || str == "floats";
  }
  bool isCorrectCount(size_t count)
  {
    return count != 0;
  }
}

int main(int argc, char** argv)
{
  std::srand(std::time(0));
  if (argc != 4)
  {
    std::cerr << "Incorrect count of args!\n";
    return 1;
  }
  std::string sorting_type = argv[1];
  std::string value_type = argv[2];
  size_t count_of_numbers = std::atoll(argv[3]);
  if (!isCorrectSortingName(sorting_type) || !isCorrectValueType(value_type) || !isCorrectCount(count_of_numbers))
  {
    std::cerr << "Incorrect args!\n";
    return 1;
  }

  if (value_type == "ints")
  {
    if (sorting_type == "ascending")
    {
      sortingLists< int >(count_of_numbers, std::less< int >(), std::cout);
    }
    else
    {
      sortingLists< int >(count_of_numbers, std::greater< int >(), std::cout);
    }
  }
  else if (value_type == "floats")
  {
    std::cout << std::fixed << std::setprecision(1);
    if (sorting_type == "ascending")
    {
      sortingLists< float >(count_of_numbers, std::less< float >(), std::cout);
    }
    else
    {
      sortingLists< float >(count_of_numbers, std::greater< float >(), std::cout);
    }
  }

  return 0;
}
