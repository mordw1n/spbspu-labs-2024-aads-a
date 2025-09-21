#include "io_files.hpp"
#include <string>
#include <iostream>
#include "forwardList.hpp"

spiridonov::ForwardList< std::string > spiridonov::readLinesFromStream(std::istream& istream)
{
  spiridonov::ForwardList< std::string > lines;
  if (!istream.eof())
  {
    std::string line;
    while (std::getline(istream, line))
    {
      if (line.size())
      {
        lines.pushBack(line);
      }
      if (istream.eof())
      {
        break;
      }
    }
  }
  return lines;
}
