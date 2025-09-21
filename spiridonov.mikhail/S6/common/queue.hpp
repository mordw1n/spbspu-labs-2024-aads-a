#ifndef QUEUE_HPP_S1
#define QUEUE_HPP_S1

#include <stdexcept>
#include "list.hpp"

namespace spiridonov
{
  template < typename T >
  class Queue
  {
  public:
    Queue() = default;

    void push(const T&);
    void drop();
    const T& getNext() const;
    bool isEmpty() const;

  private:
    detail::List< T > list_;
  };
}

template < typename T >
void spiridonov::Queue< T >::push(const T& value)
{
  list_.pushBack(value);
}

template < typename T >
void spiridonov::Queue< T >::drop()
{
  if (isEmpty())
  {
    throw std::logic_error("Queue is empty!");
  }
  list_.popFront();
}

template < typename T >
const T& spiridonov::Queue< T >::getNext() const
{
  if (isEmpty())
  {
    throw std::logic_error("Queue is empty!");
  }
  return list_.getFront();
}

template < typename T >
bool spiridonov::Queue< T >::isEmpty() const
{
  return list_.isEmpty();
}

#endif
