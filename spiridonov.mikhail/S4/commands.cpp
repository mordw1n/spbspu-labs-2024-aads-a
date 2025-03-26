#include "commands.hpp"
#include <iostream>

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

void spiridonov::complement_dict(std::istream& in, AVLtree<std::string, AVLtree<int, std::string>>& dicts)
{
  std::string new_name, first_name, second_name;
  in >> new_name >> first_name >> second_name;

  if (!dicts.contains(first_name) || !dicts.contains(second_name))
  {
    throw std::out_of_range("Dictionary not found");
  }

  const auto& first = dicts.at(first_name);
  const auto& second = dicts.at(second_name);
  AVLtree<int, std::string> res;

  for (auto it = first.cbegin(); it != first.cend(); ++it)
  {
    if (second.find(it->first) == second.cend())
    {
      res.insert(it->first, it->second);
    }
  }
  dicts.push_cmd(new_name, res);
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
