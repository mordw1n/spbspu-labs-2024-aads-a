#include "commands.hpp"
#include <iostream>

void spiridonov::create_dict(std::istream& in, mainDictsTree& dicts)
{
  std::string name = "";
  in >> name;
  if (dicts.contains(name))
  {
    std::cout << "<NAME IS BUSY>\n";
  }
  else
  {
    dicts.insert(name, dictTree());
  }
}

void spiridonov::load_dict(std::istream& in, mainDictsTree& dicts)
{
  std::string name = "", filename = "";
  in >> name >> filename;
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "<FILE NOT FOUND>\n";
    return;
  }
  dictTree& dict = dicts.at(name);
  std::string word = " ";
  int frequency = 0;
  while (file >> word >> frequency)
  {
    dict.insert(frequency, word);
  }
}

void spiridonov::add_word(std::istream& in, mainDictsTree& dicts)
{
  std::string name = "", word = "", frequency_str = "";
  in >> name >> word >> frequency_str;
  int frequency = 0;
  try
  {
    frequency = std::stoi(frequency_str);
  }
  catch (const std::invalid_argument&)
  {
    std::cerr << "<BAD VALUE>\n";
    return;
  }
  dictTree& dict = dicts.at(name);
  dict.insert(frequency, word);
}
void spiridonov::remove_word(std::istream& in, mainDictsTree& dicts)
{
  std::string name = "", word = "";
  in >> name >> word;
  dictTree& dict = dicts.at(name);
  auto it = dict.find_value(word);
  if (it != dict.end())
  {
    dict.erase(it->first);
  }
  else
  {
    std::cout << "<WORD NOT FOUND>\n";
  }
}

void spiridonov::find_freq(std::istream& in, mainDictsTree& dicts)
{
  std::string name = "", word = "";
  in >> name >> word;
  const dictTree& dict = dicts.at(name);
  auto it = dict.find_value(word);
  if (it != dict.cend())
  {
    std::cout << it->first << "\n";
  }
  else
  {
    std::cout << "<WORD NOT FOUND>\n";
  }
}


void spiridonov::display_dict(std::istream& in, const mainDictsTree& dicts, std::ostream& out)
{
  std::string in_dict_name = "";
  in >> in_dict_name;
  dictTree in_dict = dicts.at(in_dict_name);
  if (in_dict.empty())
  {
    std::cerr << "<DICTIONARY IS EMPTY>\n";
    return;
  }
  out << in_dict_name;
  for (auto it = in_dict.cbegin(); it != in_dict.cend(); it++)
  {
    out << " " << it->first << " " << it->second;
  }
  out << "\n";
}

void spiridonov::merge_dicts(std::istream& in, mainDictsTree& dicts)
{
  std::string new_name = "", first_name = "", second_name = "";
  in >> new_name >> first_name >> second_name;
  if (!dicts.contains(first_name) || !dicts.contains(second_name) || first_name == second_name)
  {
    std::cerr << "<MERGE ERROR>\n";
    return;
  }
  const dictTree& first = dicts.at(first_name);
  const dictTree& second = dicts.at(second_name);
  dictTree res = first;
  for (auto it = second.cbegin(); it != second.cend(); ++it)
  {
    res.push_cmd(it->first, it->second + res[it->first]);
  }
  dicts.push_cmd(new_name, res);
}

void spiridonov::save_to_file(std::istream& in, mainDictsTree& dicts)
{
  std::string name = "", filename = "";
  in >> name >> filename;
  if (!dicts.contains(name))
  {
    std::cerr << "<DICTIONARY IS EMPTY>\n";
    return;
  }
  std::ofstream file(filename);
  const dictTree& dict = dicts.at(name);
  for (auto it = dict.cbegin(); it != dict.cend(); ++it)
  {
    file << it->second << " " << it->first << "\n";
  }
  file.close();
}

void spiridonov::compare_dicts(std::istream& in, mainDictsTree& dicts)
{
  std::string first_name = "", second_name = "";
  in >> first_name >> second_name;
  const dictTree& first = dicts.at(first_name);
  const dictTree& second = dicts.at(second_name);
  for (auto it = first.cbegin(); it != first.cend(); ++it)
  {
    if (!second.contains(it->first))
    {
      std::cout << "\"" << it->first << "\" is not in " << second_name << "\n";
    }
  }
  for (auto it = second.cbegin(); it != second.cend(); ++it)
  {
    if (!first.contains(it->first))
    {
      std::cout << "\"" << it->first << "\" is not in " << first_name << "\n";
    }
  }
}

void spiridonov::intersect_dict(std::istream& in, mainDictsTree& dicts)
{
  std::string new_name = "", first_name = "", second_name = "";
  in >> new_name >> first_name >> second_name; 
  const auto& first = dicts.at(first_name);
  const auto& second = dicts.at(second_name);
  dictTree res;
  for (auto it = first.cbegin(); it != first.cend(); ++it)
  {
    if (second.contains(it->first))
    {
      res.insert(it->first, it->second);
    }
  }
  dicts.push_cmd(new_name, res);
}

void spiridonov::diff_dict(std::istream& in, mainDictsTree& dicts)
{
  std::string new_name = "", first_name = "", second_name = "";
  in >> new_name >> first_name >> second_name;
  const dictTree& first = dicts.at(first_name);
  const dictTree& second = dicts.at(second_name);
  dictTree res;
  for (auto it = first.cbegin(); it != first.cend(); ++it)
  {
    auto range = second.equal_range(it->first);
    if (range.first->second != it->second)
    {
      res.insert(it->first, it->second);
    }
  }
  dicts.push_cmd(new_name, res);
}

void spiridonov::union_dict(std::istream& in, mainDictsTree& dicts)
{
  std::string new_name = "", first_name = "", second_name = "";
  in >> new_name >> first_name >> second_name;
  const auto& first = dicts.at(first_name);
  const auto& second = dicts.at(second_name);
  dictTree res = first;
  for (auto it = second.cbegin(); it != second.cend(); ++it)
  {
    if (!res.contains(it->first))
    {
      res.insert(it->first, it->second);
    }
  }
  dicts.push_cmd(new_name, res);
}

void spiridonov::dict_from_file(std::istream& in, mainDictsTree& dicts)
{
  std::string name = "", filename = "";
  in >> name >> filename;
  std::ifstream file(filename);
  dictTree res;
  std::string word = "";
  int freq = 0;
  while (file >> word >> freq)
  {
    res.insert(freq, word);
  }
  file.close();
  dicts.push_cmd(name, res);
}
