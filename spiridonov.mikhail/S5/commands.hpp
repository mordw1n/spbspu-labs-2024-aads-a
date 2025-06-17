#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "../common/tree/AVLtree.hpp"

namespace spiridonov
{
  int Traverse_Ascending(std::string& result, AVLtree< int, std::string >& map);
  int Traverse_Descending(std::string& result, AVLtree< int, std::string >& map);
  int Traverse_Breadth(std::string& result, AVLtree< int, std::string >& map);
}

#endif
