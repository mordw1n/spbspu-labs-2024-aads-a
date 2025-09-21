#include "shellStrategies.hpp"

spiridonov::DivideThreeStrategy::DivideThreeStrategy(value_t size):
  d_{1}
{
  while (d_ < size / 3)
  {
    d_ = 3 * d_ + 1;
  }
}
spiridonov::DivideThreeStrategy::value_t spiridonov::DivideThreeStrategy::operator()()
{
  return d_ /= 3;
}
bool spiridonov::DivideThreeStrategy::isEnd() const
{
  return d_ < 1;
}

spiridonov::DivideTwoStrategy::DivideTwoStrategy(value_t size):
  d_{1}
{
  while (d_ < size / 2)
  {
    d_ = 2 * d_ + 1;
  }
}
spiridonov::DivideTwoStrategy::value_t spiridonov::DivideTwoStrategy::operator()()
{
  return d_ /= 2;
}
bool spiridonov::DivideTwoStrategy::isEnd() const
{
  return d_ < 1;
}

spiridonov::HibbardStrategy::HibbardStrategy(value_t size):
  size_(size),
  multiplier_(2)
{}
spiridonov::HibbardStrategy::value_t spiridonov::HibbardStrategy::operator()()
{
  multiplier_ *= 2;
  return multiplier_ - 1;
}
bool spiridonov::HibbardStrategy::isEnd() const
{
  return (multiplier_ - 1) > size_;
}