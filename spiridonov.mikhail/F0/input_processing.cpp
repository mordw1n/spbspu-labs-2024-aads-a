#include "input_processing.hpp"
#include <limits>
#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <stdexcept>

namespace spiridonov
{
  void read_dict(std::ifstream& in, AVLtree<std::string, AVLtree<int, std::string>>& dictionaries)
  {
    std::string data = "";
    std::string value = "";
    int key = 0;

    while (in >> data)
    {
      AVLtree< int, std::string > dict;
      if (in.get() == '\n')
      {
        dictionaries.insert(data, dict);
        continue;
      }
      while (in >> key >> value)
      {
        dict.insert(key, value);
        if (in.get() == '\n')
        {
          break;
        }
      }
      dictionaries.insert(data, dict);
    }
  }

  AVLtree<std::string, std::function<void(std::istream&, AVLtree<std::string, AVLtree<int, std::string>>&)> > cmds;
  void process_commands(AVLtree<std::string, AVLtree<int, std::string>>& dictionary)
  {
    using namespace std::placeholders;

    cmds["print"] = std::bind(print_dict, _1, _2, std::ref(std::cout));
    cmds["create"] = std::bind(create_dict, _1, _2);
    //cmds["complement"] = std::bind(complement_dict, _1, _2);
    cmds["intersect"] = std::bind(intersect_dict, _1, _2);
    cmds["union"] = std::bind(union_dict, _1, _2);

    std::string cmd;
    while (std::cin >> cmd)
    {
      try
      {
        cmds.at(cmd)(std::cin, dictionary);
      }
      catch (const std::exception)
      {
        std::cout << "<INVALID COMMAND>" << '\n';
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  void spiridonov::print_dict(std::istream& in, const AVLtree< std::string, AVLtree< int, std::string > >& dicts, std::ostream& out)
  {
    std::string in_dict_name = "";
    in >> in_dict_name;
    AVLtree< int, std::string > in_dict = dicts.at(in_dict_name);
    if (in_dict.empty())
    {
      out << "<EMPTY>\n";
      return;
    }
    out << in_dict_name;
    for (auto it = in_dict.cbegin(); it != in_dict.cend(); it++)
    {
      out << " " << it->first << " " << it->second;
    }
    out << "\n";
  }
}
