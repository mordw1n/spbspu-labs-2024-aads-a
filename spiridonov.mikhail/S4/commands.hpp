#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <fstream>
#include <ostream>
#include <string>
#include "AVLtree.hpp"

namespace spiridonov
{
  void print_dict(std::istream& in, const AVLtree< std::string, AVLtree< int, std::string > >& dicts, std::ostream& out);
  void complement_dict(std::istream& in, AVLtree< std::string, AVLtree< int, std::string > >& dicts);
  void intersect_dict(std::istream& in, AVLtree< std::string, AVLtree< int, std::string > >& dicts);
  void union_dict(std::istream& in, AVLtree< std::string, AVLtree< int, std::string > >& dicts);
}

#endif
