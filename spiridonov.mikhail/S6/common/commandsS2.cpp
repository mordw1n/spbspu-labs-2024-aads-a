#include "commandsS2.hpp"
#include <iostream>
#include <stdexcept>
#include "forwardList.hpp"
#include "io_files.hpp"

namespace
{
  void checkEndOfIterators(spiridonov::commands_iter_t iter_begin, spiridonov::commands_iter_t iter_end)
  {
    if (iter_begin == iter_end)
    {
      throw std::out_of_range("Out of iterators' range!");
    }
  }
}

void spiridonov::doPrint(commands_iter_t args_iter_begin, commands_iter_t args_iter_end, dicts_t& dicts, std::ostream& os)
{
  checkEndOfIterators(args_iter_begin, args_iter_end);
  dict_name_t dict_name = *(args_iter_begin++);
  dicts_t::Iterator dict_to_print_iter = dicts.get(dict_name);

  if (args_iter_begin == args_iter_end && dict_to_print_iter != dicts.end())
  {
    dict_t& dict_to_print = dict_to_print_iter->second;
    if (dict_to_print.isEmpty())
    {
      throw std::length_error("Empty!");
    }
    else
    {
      os << dict_name;
      for (auto&& data: dict_to_print)
      {
        os << ' ' << data.first << ' ' << data.second;
      }
      os << '\n';
    }
  }
  else
  {
    throw std::out_of_range("Out of iterators' range!");
  }
}

void spiridonov::doComplement(commands_iter_t args_iter_begin, commands_iter_t args_iter_end, dicts_t& dicts)
{
  checkEndOfIterators(args_iter_begin, args_iter_end);
  dict_name_t new_dict_name = *(args_iter_begin++);

  checkEndOfIterators(args_iter_begin, args_iter_end);
  dict_name_t first_dict_name = *(args_iter_begin++);

  checkEndOfIterators(args_iter_begin, args_iter_end);
  dict_name_t second_dict_name = *(args_iter_begin++);

  dicts_t::Iterator first_dict_iter = dicts.get(first_dict_name);
  dicts_t::Iterator second_dict_iter = dicts.get(second_dict_name);

  bool is_dicts_exist = first_dict_iter != dicts.end() && second_dict_iter != dicts.end();
  if (args_iter_begin == args_iter_end && is_dicts_exist)
  {
    dict_t first_dict = first_dict_iter->second;
    dict_t second_dict = second_dict_iter->second;
    dict_t new_dict;
    for (auto&& first_data: first_dict)
    {
      bool is_unique = true;
      for (auto&& second_data: second_dict)
      {
        is_unique = first_data.first != second_data.first;
        if (!is_unique)
        {
          break;
        }
      }
      if (is_unique)
      {
        new_dict.push(first_data.first, first_data.second);
      }
    }
    dicts_t::Iterator new_dict_iter = dicts.get(new_dict_name);
    if (new_dict_iter == dicts.end())
    {
      dicts.push(new_dict_name, new_dict);
    }
    else
    {
      new_dict_iter->second = new_dict;
    }
  }
  else
  {
    throw std::out_of_range("Out of iterators' range!");
  }
}

void spiridonov::doIntersect(commands_iter_t args_iter_begin, commands_iter_t args_iter_end, dicts_t& dicts)
{
  checkEndOfIterators(args_iter_begin, args_iter_end);
  dict_name_t new_dict_name = *(args_iter_begin++);

  checkEndOfIterators(args_iter_begin, args_iter_end);
  dict_name_t first_dict_name = *(args_iter_begin++);

  checkEndOfIterators(args_iter_begin, args_iter_end);
  dict_name_t second_dict_name = *(args_iter_begin++);

  dicts_t::Iterator first_dict_iter = dicts.get(first_dict_name);
  dicts_t::Iterator second_dict_iter = dicts.get(second_dict_name);

  bool is_dicts_exist = first_dict_iter != dicts.end() && second_dict_iter != dicts.end();
  if (args_iter_begin == args_iter_end && is_dicts_exist)
  {
    dict_t first_dict = first_dict_iter->second;
    dict_t second_dict = second_dict_iter->second;
    dict_t new_dict;
    for (auto&& first_data: first_dict)
    {
      for (auto&& second_data: second_dict)
      {
        if (first_data.first == second_data.first)
        {
          new_dict.push(first_data.first, first_data.second);
        }
      }
    }
    dicts_t::Iterator new_dict_iter = dicts.get(new_dict_name);
    if (new_dict_iter == dicts.end())
    {
      dicts.push(new_dict_name, new_dict);
    }
    else
    {
      new_dict_iter->second = new_dict;
    }
  }
  else
  {
    throw std::out_of_range("Out of iterators' range!");
  }
}

void spiridonov::doUnion(commands_iter_t args_iter_begin, commands_iter_t args_iter_end, dicts_t& dicts)
{
  checkEndOfIterators(args_iter_begin, args_iter_end);
  dict_name_t new_dict_name = *(args_iter_begin++);

  checkEndOfIterators(args_iter_begin, args_iter_end);
  dict_name_t first_dict_name = *(args_iter_begin++);

  checkEndOfIterators(args_iter_begin, args_iter_end);
  dict_name_t second_dict_name = *(args_iter_begin++);

  dicts_t::Iterator first_dict_iter = dicts.get(first_dict_name);
  dicts_t::Iterator second_dict_iter = dicts.get(second_dict_name);

  bool is_dicts_exist = first_dict_iter != dicts.end() && second_dict_iter != dicts.end();
  if (args_iter_begin == args_iter_end && is_dicts_exist)
  {
    dict_t first_dict = first_dict_iter->second;
    dict_t second_dict = second_dict_iter->second;
    dict_t new_dict;
    for (auto&& first_data: first_dict)
    {
      new_dict.push(first_data.first, first_data.second);
    }
    for (auto&& second_data: second_dict)
    {
      bool is_unique = true;
      for (auto&& first_data: first_dict)
      {
        is_unique = second_data.first != first_data.first;
        if (!is_unique)
        {
          break;
        }
      }
      if (is_unique)
      {
        new_dict.push(second_data.first, second_data.second);
      }
    }
    dicts_t::Iterator new_dict_iter = dicts.get(new_dict_name);
    if (new_dict_iter == dicts.end())
    {
      dicts.push(new_dict_name, new_dict);
    }
    else
    {
      new_dict_iter->second = new_dict;
    }
  }
  else
  {
    throw std::out_of_range("Out of iterators' range!");
  }
}

spiridonov::dicts_t spiridonov::getDictsFromStream(std::istream& istream)
{
  dicts_t dicts;
  spiridonov::ForwardList< std::string > lines = readLinesFromStream(istream);
  for (std::string& line: lines)
  {
    spiridonov::Words words(line);
    auto words_iter_b = words.begin();
    auto words_iter_e = words.end();

    std::string dict_name = *(words_iter_b++);

    dict_t new_dict;
    while (words_iter_b != words_iter_e)
    {
      int key = std::stoi(*(words_iter_b++));
      std::string value = *(words_iter_b++);
      new_dict.push(key, value);
    }
    dicts.push(dict_name, new_dict);
  }
  return dicts;
}
