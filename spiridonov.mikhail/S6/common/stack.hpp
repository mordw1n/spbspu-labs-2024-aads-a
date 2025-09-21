#ifndef STACK_HPP_S1
#define STACK_HPP_S1

#include <stdexcept>
#include "list.hpp"

namespace spiridonov
{
  template < typename T >
  class Stack
  {
  public:
    Stack() = default;

    void push(const T&);
    void drop();
    const T& getTop() const;
    bool isEmpty() const;

  private:
    detail::List< T > list_;
  };
}

template < typename T >
void spiridonov::Stack< T >::push(const T& value)
{
  list_.pushFront(value);
}

template < typename T >
void spiridonov::Stack< T >::drop()
{
  if (isEmpty())
  {
    throw std::logic_error("Stack is empty!");
  }
  list_.popFront();
}

template < typename T >
const T& spiridonov::Stack< T >::getTop() const
{
  if (isEmpty())
  {
    throw std::logic_error("Stack is empty!");
  }
  return list_.getFront();
}

template < typename T >
bool spiridonov::Stack< T >::isEmpty() const
{
  return list_.isEmpty();
}

#endif
