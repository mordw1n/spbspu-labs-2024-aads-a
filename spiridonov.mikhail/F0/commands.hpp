#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <fstream>
#include <ostream>
#include <string>
#include "AVLtree.hpp"

namespace spiridonov
{
  using dictTree = AVLtree< int, std::string >;
  using mainDictsTree = AVLtree< std::string, dictTree >;

  void create_dict(std::istream& in, mainDictsTree& dicts);
  void load_dict(std::istream& in, mainDictsTree& dicts);
  void add_word(std::istream& in, mainDictsTree& dicts);
  void remove_word(std::istream& in, mainDictsTree& dicts);
  void find_freq(std::istream& in, mainDictsTree& dicts);
  void display_dict(std::istream& in, const mainDictsTree& dicts, std::ostream& out);
  void merge_dicts(std::istream& in, mainDictsTree& dicts);
  void save_to_file(std::istream& in, mainDictsTree& dicts);
  void compare_dicts(std::istream& in, mainDictsTree& dicts);
  void intersect_dict(std::istream& in, mainDictsTree& dicts);
  void diff_dict(std::istream& in, mainDictsTree& dicts);
  void union_dict(std::istream& in, mainDictsTree& dicts);
  void dict_from_file(std::istream& in, mainDictsTree& dicts);
}

#endif
