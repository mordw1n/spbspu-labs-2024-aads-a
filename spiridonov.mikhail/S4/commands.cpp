#include "commands.hpp"

void spiridonov::read_dict(std::ifstream& in, dict & dictionaries)
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

void spiridonov::print_dict(std::ostream& out, const dict& out_dict)
{

}

void spiridonov::complement_dict(dict& new_dict, const dict& first_dict, const dict& second_dict)
{

}

void spiridonov::intersect_dict(dict& new_dict, const dict& first_dict, const dict& second_dict)
{

}

void spiridonov::union_dict(dict& new_dict, const dict& first_dict, const dict& second_dict)
{

}
