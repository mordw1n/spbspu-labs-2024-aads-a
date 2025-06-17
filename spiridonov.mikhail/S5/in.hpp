#ifndef INPUT_HPP
#define INPUT_HPP
#include "../common/tree/AVLtree.hpp"
namespace spiridonov
{
  AVLtree< int, std::string > input(std::istream&);
}

#endif
