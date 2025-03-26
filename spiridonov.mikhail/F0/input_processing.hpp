#ifndef INPUT_PROCESSING_HPP
#define INPUT_PROCESSING_HPP

#include <functional>
#include "commands.hpp"

namespace spiridonov
{
  void read_dict(std::ifstream& in, AVLtree< std::string, AVLtree< int, std::string > >& dictionaries);
  void process_commands(AVLtree<std::string, AVLtree<int, std::string>>& dictionary);
  void print_dict(std::istream& in, const AVLtree< std::string, AVLtree< int, std::string > >& dicts, std::ostream& out);
}

#endif