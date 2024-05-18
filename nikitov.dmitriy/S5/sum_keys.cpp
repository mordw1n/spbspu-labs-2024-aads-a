#include "sum_keys.hpp"
#include <limits>
#include <stdexcept>

void nikitov::SumKeys::operator()(const std::pair< int, std::string >& value)
{
  line_ += value.second;
  int min = std::numeric_limits< int >::min();
  int max = std::numeric_limits< int >::max();
  if ((key_ > 0 && max - key_ < value.first) || (key_ < 0 && value.first < 0 && min - key_ > value.first))
  {
    throw std::overflow_error("Error: numeric overflow");
  }
  key_ += value.first;
}

int nikitov::SumKeys::getKey() const
{
  return key_;
}

std::string nikitov::SumKeys::getLine() const
{
  return line_;
}