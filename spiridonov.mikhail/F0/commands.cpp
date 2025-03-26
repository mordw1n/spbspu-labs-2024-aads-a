#include "commands.hpp"
#include <iostream>

void spiridonov::create_dict(std::istream& in, AVLtree<std::string, AVLtree<int, std::string>>& dicts)
{
  std::string name;
  in >> name;
  if (dicts.contains(name))
  {
    std::cout << "<NAME IS BUSY>\n";
  }
  else
  {
    dicts.push_cmd(name, AVLtree<int, std::string>());
  }
}

void spiridonov::load_dict()
{

}

void spiridonov::add_word()
{

}

void spiridonov::remove_word()
{

}

void spiridonov::find_freq()
{

}

void spiridonov::display_dict()
{

}

void spiridonov::merge()
{

}

void spiridonov::save_to_file()
{

}

void spiridonov::compare()
{

}

void spiridonov::intersect_dict(std::istream& in, AVLtree< std::string, AVLtree< int, std::string > >& dicts)
{
  std::string new_name, first_name, second_name;
  in >> new_name >> first_name >> second_name;
  
  const auto& first = dicts.at(first_name);
  const auto& second = dicts.at(second_name);
  AVLtree<int, std::string> res;

  if (!dicts.contains(first_name) || !dicts.contains(second_name))
  {
    throw std::out_of_range("Dictionary not found");
  }
  for (auto it = first.cbegin(); it != first.cend(); ++it)
  {
    if (second.contains(it->first))
    {
      res.insert(it->first, it->second);
    }
  }
  dicts.push_cmd(new_name, res);
}

void spiridonov::diff_dict()
{

}

void spiridonov::union_dict(std::istream& in, AVLtree< std::string, AVLtree< int, std::string > >& dicts)
{
  std::string new_name, first_name, second_name;
  in >> new_name >> first_name >> second_name;

  if (!dicts.contains(first_name) || !dicts.contains(second_name))
  {
    throw std::out_of_range("Dictionary not found");
  }

  const auto& first = dicts.at(first_name);
  const auto& second = dicts.at(second_name);
  AVLtree< int, std::string > res = first;

  for (auto it = second.cbegin(); it != second.cend(); ++it)
  {
    if (!res.contains(it->first))
    {
      res.insert(it->first, it->second);
    }
  }
  dicts.push_cmd(new_name, res);
}

void spiridonov::dict_from_file()
{

}
