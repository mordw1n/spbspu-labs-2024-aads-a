#include <iostream>
#include "input_processing.hpp"
#include "AVLtree.hpp"
#include "t_node.hpp"
#include "commands.hpp"

int main()
{
  using namespace spiridonov;
  mainDictsTree dictionaries;
  process_commands(dictionaries);
}
