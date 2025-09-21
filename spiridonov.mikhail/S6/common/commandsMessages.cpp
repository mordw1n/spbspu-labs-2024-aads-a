#include "commandsMessages.hpp"
#include <iostream>

void spiridonov::outError(std::ostream& stream)
{
  stream << "<INVALID COMMAND>\n";
}

void spiridonov::outEmpty(std::ostream& stream)
{
  stream << "<EMPTY>\n";
}

void spiridonov::outTrue(std::ostream& stream)
{
  stream << "<TRUE>\n";
}

void spiridonov::outFalse(std::ostream& stream)
{
  stream << "<FALSE>\n";
}
