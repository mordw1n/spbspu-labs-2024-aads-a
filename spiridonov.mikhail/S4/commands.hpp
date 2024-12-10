#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <fstream>
#include <ostream>
#include <string>
#include "AVLtree.hpp"

namespace spiridonov
{
  using dict = AVLtree<std::string, AVLtree< int, std::string > >;

  void read_dict(std::ifstream & in, dict & dictionaries);

  void print_dict(std::ostream & out, const dict & out_dict);
  void complement_dict(dict & new_dict, const dict & first_dict, const dict & second_dict);
  void intersect_dict(dict & new_dict, const dict & first_dict, const dict & second_dict);
  void union_dict(dict & new_dict, const dict & first_dict, const dict & second_dict);

}

#endif
