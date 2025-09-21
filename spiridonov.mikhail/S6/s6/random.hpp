#ifndef RANDOM_HPP_S6
#define RANDOM_HPP_S6

#include <random>

namespace spiridonov
{
  template < typename T >
  T generateRand()
  {
    return 1.f / rand() * RAND_MAX;
  }
}

#endif