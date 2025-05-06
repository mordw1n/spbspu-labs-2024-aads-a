#include "commands.hpp"
#include <iostream>

void spiridonov::create_dict(std::istream& in, mainDictsTree& dicts)
{
  std::string name;
  in >> name;
  if (dicts.contains(name))
  {
    std::cerr << "<NAME IS BUSY>\n";
    return;
  }
  else
  {
    dicts.insert(name, dictTree());
  }
}

void spiridonov::load_dict(std::istream& in, mainDictsTree& dicts)
{
  std::string name, filename, word;
  in >> name >> filename;
  dicts.insert(name, dictTree());
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "<FILE NOT FOUND>\n";
    return;
  }
  int freq = 0;
  while (file >> word >> freq)
  {
    dictTree& dict = dicts.at(name);
    if (dict.contains(word))
    {
      dict[word] += freq;
    }
    else
    {
      dict.insert(word, freq);
    }
  }
}

void spiridonov::add_word(std::istream& in, mainDictsTree& dicts)
{
  std::string name, word, frequency_str;
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
  try
  {
    dictTree& dict = dicts.at(name);
    if (dict.contains(word))
    {
      dict[word] += frequency;
    }
    else
    {
      dict.insert(word, frequency);
    }
  }
  catch (const std::out_of_range&)
  {
    std::cerr << "<DICTIONARY NOT FOUND>\n";
  }
}

void spiridonov::remove_word(std::istream& in, mainDictsTree& dicts)
{
  std::string name, word;
  in >> name >> word;
  dictTree& dict = dicts.at(name);
  auto it = dict.find(word);
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
  std::string name, word;
  in >> name >> word;
  const dictTree& dict = dicts.at(name);
  auto it = dict.find(word);
  if (it != dict.cend())
  {
    std::cout << it->second << "\n";
  }
  else
  {
    std::cout << "<WORD NOT FOUND>\n";
  }
}

void spiridonov::display_dict(std::istream& in, const mainDictsTree& dicts, std::ostream& out)
{
  std::string in_dict_name;
  in >> in_dict_name;
  dictTree in_dict = dicts.at(in_dict_name);
  if (in_dict.empty())
  {
    std::cerr << "<DICTIONARY IS EMPTY>\n";
    return;
  }
  out << in_dict_name << ":";
  for (auto it = in_dict.cbegin(); it != in_dict.cend(); it++)
  {
    out << " " << it->first << " " << it->second << "\n";;
  }
}

void spiridonov::merge_dicts(std::istream& in, mainDictsTree& dicts)
{
  std::string new_name, first_name, second_name;
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
  std::string name, filename;
  in >> filename >> name;
  const dictTree& dict = dicts.at(name);
  std::ofstream file(filename);
  if (dict.empty())
  {
    std::cerr << "<DICTIONARY IS EMPTY>\n";
    return;
  }
  for (auto it = dict.cbegin(); it != dict.cend(); ++it)
  {
    file << it->first << " " << it->second << "\n";
  }
}

void spiridonov::compare_dicts(std::istream& in, mainDictsTree& dicts)
{
  std::string first_name, second_name;
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
  std::string new_name, first_name, second_name;
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
  std::string new_name, first_name, second_name;
  in >> new_name >> first_name >> second_name;
  const dictTree& first = dicts.at(first_name);
  const dictTree& second = dicts.at(second_name);
  dictTree res;
  for (auto it = first.cbegin(); it != first.cend(); ++it)
  {
    auto range = second.equal_range(it->first);
    if (range.first == second.cend() || range.first->second != it->second)
    {
      res.insert(it->first, it->second);
    }
  }
  dicts.push_cmd(new_name, res);
}

void spiridonov::union_dict(std::istream& in, mainDictsTree& dicts)
{
  std::string new_name, first_name, second_name;
  in >> new_name >> first_name >> second_name;
  try
  {
    const dictTree& first = dicts.at(first_name);
    const dictTree& second = dicts.at(second_name);

    dictTree res = first;

    for (auto it = second.cbegin(); it != second.cend(); ++it)
    {
      if (res.contains(it->first))
      {
        res[it->first] += it->second;
      }
      else
      {
        res.insert(it->first, it->second);
      }
    }
    dicts.push_cmd(new_name, res);
  }
  catch (const std::out_of_range&)
  {
    std::cerr << "<SOME DICTIONARY NOT FOUND>\n";
  }
}

void spiridonov::dict_from_file(std::istream& in, mainDictsTree& dicts)
{
  std::string name, filename, word;
  in >> filename >> name;
  dicts.insert(name, dictTree());
  std::ifstream file(filename);
  int freq = 0;
  while (file >> word)
  {
    dictTree& dict = dicts.at(name);
    if (dict.contains(word))
    {
      dict[word] += 1;
    }
    else
    {
      dict.insert(word, 1);
    }
  }
}
