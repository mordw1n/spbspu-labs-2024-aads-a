#include "in.hpp"

spiridonov::AVLtree< int, std::string > spiridonov::input(std::istream& in)
{
  int key = 0;
  std::string value = "";
  AVLtree< int, std::string > map;
  while (in)
  {
    while (in >> key >> value)
    {
      map.insert(key, value);
    }
    if (!in.eof())
    {
      throw std::logic_error("Bad input");
    }
  }
  return map;
}
