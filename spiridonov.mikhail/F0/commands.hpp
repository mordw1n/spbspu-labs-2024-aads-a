#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <fstream>
#include <ostream>
#include <string>
#include "AVLtree.hpp"

namespace spiridonov
{
  void create_dict(std::istream& in, AVLtree<std::string, AVLtree<int, std::string>>& dicts);
  void load_dict();
  void add_word();
  void remove_word();
  void find_freq();
  void display_dict();
  void merge();
  void save_to_file();
  void compare();
  void intersect_dict(std::istream& in, AVLtree< std::string, AVLtree< int, std::string > >& dicts);
  void diff_dict();
  void union_dict(std::istream& in, AVLtree< std::string, AVLtree< int, std::string > >& dicts);
  void dict_from_file();
}

#endif
