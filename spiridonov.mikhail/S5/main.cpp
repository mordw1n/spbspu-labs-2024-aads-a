#include <iostream>
#include <fstream>
#include "../common/tree/AVLtree.hpp"
#include "commands.hpp"
#include "in.hpp"

int main(int argc, char* argv[])
{
  using namespace spiridonov;
  AVLtree< int, std::string > map;
  if (argc == 3)
  {
    try
    {
      std::ifstream file(argv[2]);
      map = input(file);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }
  else
  {
    std::cerr << "<INVALID ARGUMENTS>\n";
    return 2;
  }

  AVLtree< std::string, std::function< int(std::string& result, AVLtree< int, std::string >& map) > > cmds;
  cmds.insert("ascending", Traverse_Ascending);
  cmds.insert("descending", Traverse_Descending);
  cmds.insert("breadth", Traverse_Breadth);

  std::string command(argv[1]);
  std::string cmd_out = "";
  int total = 0;
  try
  {
    total = cmds.at(command)(cmd_out, map);
    if (!cmd_out.empty())
    {
      cmd_out.pop_back();
      if (cmd_out != "<EMPTY>")
      {
        std::cout << total << " ";
      }
      std::cout << cmd_out << "\n";
    }
  }
  catch (const std::invalid_argument)
  {
    std::cerr << "<INVALID COMMAND>\n";
    return 1;
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << e.what();
    return 1;
  }
  catch (const std::logic_error& e)
  {
    std::cout << e.what() << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }
}
