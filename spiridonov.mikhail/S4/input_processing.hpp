#ifndef INPUT_PROCESSING_HPP
#define INPUT_PROCESSING_HPP

#include "commands.hpp"

namespace spiridonov
{
  void read_dict(std::ifstream& in, dict& dictionaries);
  std::ostream& commands(std::istream& in, std::ostream& out, dict& some_dict);
}

#endif
