#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <stdexcept>
#include <limits>
#include "commands.hpp"

namespace spiridonov
{
  void process_commands(mainDictsTree& dictionaries)
  {
    using namespace std::placeholders;

    AVLtree< std::string, std::function< void(std::istream&, mainDictsTree&) > > cmds;
    cmds.insert("create", std::bind(create_dict, _1, _2));
    cmds.insert("load", std::bind(load_dict, _1, _2));
    cmds.insert("add_word", std::bind(add_word, _1, _2));
    cmds.insert("remove_word", std::bind(remove_word, _1, _2));
    cmds.insert("find", std::bind(find_freq, _1, _2));
    cmds.insert("display", std::bind(display_dict, _1, _2, std::ref(std::cout)));
    cmds.insert("merge", std::bind(merge_dicts, _1, _2));
    cmds.insert("save", std::bind(save_to_file, _1, _2));
    cmds.insert("compare", std::bind(compare_dicts, _1, _2));
    cmds.insert("intersect", std::bind(intersect_dict, _1, _2));
    cmds.insert("diff", std::bind(diff_dict, _1, _2));
    cmds.insert("union", std::bind(union_dict, _1, _2));
    cmds.insert("dict_ff", std::bind(dict_from_file, _1, _2));

    std::string cmd = "";
    while (std::cin >> cmd)
    {
      try
      {
        cmds.at(cmd)(std::cin, dictionaries);
      }
      catch (const std::exception)
      {
        std::cout << "<INVALID COMMAND>" << '\n';
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
