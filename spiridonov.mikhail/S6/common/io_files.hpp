#ifndef IO_FILES_HPP_S2
#define IO_FILES_HPP_S2

#include <string>
#include <iosfwd>
#include "forwardList.hpp"

namespace spiridonov
{
  spiridonov::ForwardList< std::string > readLinesFromStream(std::istream& istream);
}

#endif
