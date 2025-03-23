#include <iostream>
#include "input_processing.hpp"
#include "AVLtree.hpp"
#include "t_node.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace spiridonov;
  AVLtree< std::string, AVLtree< int, std::string > > dictionaries;
  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    if (file)
    {
      read_dict(file, dictionaries);
    }
    else
    {
      std::cerr << "Error to open file\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "File not found\n";
    return 1;
  }
  process_commands(dictionaries);
}

