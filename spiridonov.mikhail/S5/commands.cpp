#include "commands.hpp"
#include <limits>
#include <string>

struct Key_summ
{
public:
  Key_summ();
  void operator()(const std::pair< const int, std::string >& key_value);
  int getRes() const;
  std::string getStr() const;

private:
  int res_;
  std::string str_;
};

Key_summ::Key_summ():
  res_(0),
  str_("")
{}

void Key_summ::operator()(const std::pair< const int, std::string >& key_value)
{
  constexpr int maxNumber = std::numeric_limits< int >::max();
  constexpr int minNumber = std::numeric_limits< int >::min();
  if ((res_ > 0 && maxNumber - res_ < key_value.first) || (res_ < 0 && key_value.first < 0 && minNumber - res_ > key_value.first))
  {
    throw std::overflow_error("Expected overflow or underflow");
  }
  res_ += key_value.first;
  str_ += key_value.second + " ";
}

int Key_summ::getRes() const
{
  return res_;
}

std::string Key_summ::getStr() const
{
  return str_;
}

int spiridonov::Traverse_Ascending(std::string& result, AVLtree< int, std::string >& map)
{
  Key_summ total;
  total = map.traverse_lnr(total);
  int summ = total.getRes();
  result = total.getStr();
  return summ;
}

int spiridonov::Traverse_Descending(std::string& result, AVLtree< int, std::string >& map)
{
  Key_summ total;
  total = map.traverse_rnl(total);
  int summ = total.getRes();
  result = total.getStr();
  return summ;
}

int::spiridonov::Traverse_Breadth(std::string& result, AVLtree< int, std::string >& map)
{
  Key_summ total;
  total = map.traverse_breadth(total);
  int summ = total.getRes();
  result = total.getStr();
  return summ;
}