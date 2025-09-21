#ifndef SHELL_STRATEGIES_HPP
#define SHELL_STRATEGIES_HPP

#include <cstddef>

namespace spiridonov
{
  struct DivideThreeStrategy
  {
    using value_t = std::ptrdiff_t;
    DivideThreeStrategy(value_t size);
    value_t operator()();
    bool isEnd() const;

  private:
    value_t d_;
  };

  struct DivideTwoStrategy
  {
    using value_t = std::ptrdiff_t;
    DivideTwoStrategy(value_t size);
    value_t operator()();
    bool isEnd() const;

  private:
    value_t d_;
  };

  struct HibbardStrategy
  {
    using value_t = std::ptrdiff_t;
    HibbardStrategy(value_t size);
    value_t operator()();
    bool isEnd() const;

  private:
    value_t size_;
    value_t multiplier_;
  };
}

#endif