#include "input_processing.hpp"

void spiridonov::read_dict(std::ifstream& in, dict& dictionaries)
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

std::ostream& spiridonov::commands(std::istream& in, std::ostream& out, dict& some_dict)
{

}
