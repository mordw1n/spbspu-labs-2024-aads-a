#include "mathoverflow.hpp"
#include <limits>
#include <stdexcept>

long long spiridonov::summarize(long long a, long long b)
{
  if (a > 0 && b > 0)
  {
    long long max_lli = std::numeric_limits< long long >::max();
    if (a > max_lli - b)
    {
      throw std::overflow_error("Overflow!");
    }
  }
  else if (a < 0 && b < 0)
  {
    long long min_lli = std::numeric_limits< long long >::min();
    if (a < min_lli - b)
    {
      throw std::overflow_error("Overflow!");
    }
  }
  return a + b;
}
long long spiridonov::multiply(long long a, long long b)
{
  if ((a > 0 && b > 0) || (a < 0 && b < 0))
  {
    long long max_lli = std::numeric_limits< long long >::max();
    if (a > max_lli / b)
    {
      throw std::overflow_error("Overflow!");
    }
  }
  else if ((a < 0 && b > 0) || (a > 0 && b < 0))
  {
    long long min_lli = std::numeric_limits< long long >::min();
    if (a < min_lli / b)
    {
      throw std::overflow_error("Overflow!");
    }
  }
  return a * b;
}
long long spiridonov::divide(long long a, long long b)
{
  if (!b)
  {
    throw std::logic_error("Division by zero!");
  }
  long long min = std::numeric_limits< long long >::min();
  if (a == min && b == -1)
  {
    throw std::overflow_error("Overflow!");
  }
  return a / b;
}
