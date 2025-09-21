#ifndef COMMANDS_HPP_S2
#define COMMANDS_HPP_S2

#include <iosfwd>
#include "words.hpp"
#include "dictionary.hpp"

namespace spiridonov
{
  using commands_iter_t = Words::Iterator;

  using dict_name_t = std::string;
  using dict_t = Dictionary< int, std::string, std::less< int > >;
  using dicts_t = Dictionary< dict_name_t, dict_t, std::less< dict_name_t > >;

  void doPrint(commands_iter_t, commands_iter_t, dicts_t&, std::ostream&);
  void doComplement(commands_iter_t, commands_iter_t, dicts_t&);
  void doIntersect(commands_iter_t, commands_iter_t, dicts_t&);
  void doUnion(commands_iter_t, commands_iter_t, dicts_t&);

  dicts_t getDictsFromStream(std::istream&);
}

#endif
