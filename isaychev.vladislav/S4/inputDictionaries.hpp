#ifndef INPUTDICTIONARIES_HPP
#define INPUTDICTIONARIES_HPP

#include <iosfwd>
#include <string>
#include "tree.hpp"

namespace isaychev
{
  using dataset_t = BSTree< int, std::string >;
  using map_t = BSTree< std::string, dataset_t >;
  void inputDictionaries(std::istream & in, map_t & dicts);
  void print(std::ostream & out, const std::string & name, const map_t & dicts);
}

#endif
