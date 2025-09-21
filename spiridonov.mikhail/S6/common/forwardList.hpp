#ifndef FORWARD_LIST_HPP_S2
#define FORWARD_LIST_HPP_S2

#include <cassert>
#include <iterator>
#include "list.hpp"

namespace spiridonov
{
  template < typename T >
  class ForwardList: protected detail::List< T >
  {
  public:
    using node_t = typename detail::List< T >::node_t;
    class Iterator;
    class ConstIterator;

    ForwardList() = default;

    void pushFront(const T&);
    void pushBack(const T&);
    void insert(const T&, Iterator);
    void erase(Iterator);
    bool isEmpty() const noexcept;

    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;
  };
}

template < typename T >
class spiridonov::ForwardList< T >::Iterator: public std::iterator< std::forward_iterator_tag, T >
{
public:
  friend class ForwardList< T >;
  using this_t = Iterator;
  using node_t = typename detail::List< T >::node_t;

  Iterator();
  Iterator(const this_t&) = default;
  Iterator(ConstIterator);
  ~Iterator() = default;
  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);

  T& operator*();
  T* operator->();
  const T& operator*() const;
  const T* operator->() const;

  bool operator!=(const this_t&) const;
  bool operator==(const this_t&) const;

private:
  ConstIterator iter_;
};

template < typename T >
spiridonov::ForwardList< T >::Iterator::Iterator():
  iter_()
{}
template < typename T >
spiridonov::ForwardList< T >::Iterator::Iterator(ConstIterator iter):
  iter_(iter)
{}

template < typename T >
typename spiridonov::ForwardList< T >::Iterator& spiridonov::ForwardList< T >::Iterator::operator++()
{
  ++iter_;
  return *this;
}
template < typename T >
typename spiridonov::ForwardList< T >::Iterator spiridonov::ForwardList< T >::Iterator::operator++(int)
{
  return Iterator(iter_++);
}
template < typename T >
bool spiridonov::ForwardList< T >::Iterator::operator==(const this_t& rhs) const
{
  return iter_ == rhs.iter_;
}
template < typename T >
bool spiridonov::ForwardList< T >::Iterator::operator!=(const this_t& rhs) const
{
  return !(rhs == *this);
}
template < typename T >
T& spiridonov::ForwardList< T >::Iterator::operator*()
{
  return const_cast< T& >(*iter_);
}
template < typename T >
T* spiridonov::ForwardList< T >::Iterator::operator->()
{
  return std::addressof(const_cast< T& >(*iter_));
}
template < typename T >
const T& spiridonov::ForwardList< T >::Iterator::operator*() const
{
  return *iter_;
}
template < typename T >
const T* spiridonov::ForwardList< T >::Iterator::operator->() const
{
  return std::addressof(*iter_);
}

template < typename T >
class spiridonov::ForwardList< T >::ConstIterator: public std::iterator< std::forward_iterator_tag, T >
{
public:
  friend class ForwardList< T >;
  using this_t = ConstIterator;
  using node_t = typename detail::List< T >::node_t;

  ConstIterator();
  ConstIterator(const this_t&) = default;
  ConstIterator(Iterator);
  ~ConstIterator() = default;
  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);

  const T& operator*() const;
  const T* operator->() const;

  bool operator!=(const this_t&) const;
  bool operator==(const this_t&) const;

private:
  node_t* node_;
  const ForwardList< T >* list_;

  ConstIterator(node_t* node, const ForwardList< T >* list);
};

template < typename T >
spiridonov::ForwardList< T >::ConstIterator::ConstIterator():
  node_(nullptr),
  list_(nullptr)
{}
template < typename T >
spiridonov::ForwardList< T >::ConstIterator::ConstIterator(node_t* node, const ForwardList< T >* list):
  node_(node),
  list_(list)
{}

template < typename T >
typename spiridonov::ForwardList< T >::ConstIterator& spiridonov::ForwardList< T >::ConstIterator::operator++()
{
  assert(node_ != nullptr);
  node_ = node_->next_;
  return *this;
}
template < typename T >
typename spiridonov::ForwardList< T >::ConstIterator spiridonov::ForwardList< T >::ConstIterator::operator++(int)
{
  assert(node_ != nullptr);
  this_t result(*this);
  ++(*this);
  return result;
}
template < typename T >
bool spiridonov::ForwardList< T >::ConstIterator::operator==(const this_t& rhs) const
{
  return node_ == rhs.node_ && list_ == rhs.list_;
}
template < typename T >
bool spiridonov::ForwardList< T >::ConstIterator::operator!=(const this_t& rhs) const
{
  return !(rhs == *this);
}
template < typename T >
const T& spiridonov::ForwardList< T >::ConstIterator::operator*() const
{
  assert(node_ != nullptr);
  return node_->data_;
}
template < typename T >
const T* spiridonov::ForwardList< T >::ConstIterator::operator->() const
{
  assert(node_ != nullptr);
  return std::addressof(node_->data_);
}

template < typename T >
void spiridonov::ForwardList< T >::pushFront(const T& value)
{
  detail::List< T >::pushFront(value);
}

template < typename T >
void spiridonov::ForwardList< T >::pushBack(const T& value)
{
  detail::List< T >::pushBack(value);
}

template < typename T >
void spiridonov::ForwardList< T >::insert(const T& value, Iterator iter)
{
  if (iter == end())
  {
    this->pushBack(value);
  }
  else if (iter == begin())
  {
    this->pushFront(value);
  }
  else
  {
    node_t* temp_node = this->head_;
    Iterator temp_iter = begin();
    while (++temp_iter != iter)
    {
      temp_node = temp_node->next_;
    }
    temp_node->next_ = new node_t{value, temp_node->next_};
  }
}

template < typename T >
void spiridonov::ForwardList< T >::erase(Iterator iter)
{
  if (iter == begin())
  {
    this->popFront();
  }
  else
  {
    node_t* temp_node = this->head_;
    Iterator temp_iter = begin();
    while (++temp_iter != iter)
    {
      temp_node = temp_node->next_;
    }
    node_t* next_next_node = temp_node->next_->next_;
    delete temp_node->next_;
    temp_node->next_ = next_next_node;
    if (!next_next_node)
    {
      this->tail_ = temp_node;
    }
  }
}

template < typename T >
bool spiridonov::ForwardList< T >::isEmpty() const noexcept
{
  return detail::List< T >::isEmpty();
}

template < typename T >
typename spiridonov::ForwardList< T >::Iterator spiridonov::ForwardList< T >::begin() noexcept
{
  return ConstIterator(this->head_, this);
}

template < typename T >
typename spiridonov::ForwardList< T >::Iterator spiridonov::ForwardList< T >::end() noexcept
{
  return ConstIterator(nullptr, this);
}

template < typename T >
typename spiridonov::ForwardList< T >::ConstIterator spiridonov::ForwardList< T >::begin() const noexcept
{
  return ConstIterator(this->head_, this);
}

template < typename T >
typename spiridonov::ForwardList< T >::ConstIterator spiridonov::ForwardList< T >::end() const noexcept
{
  return ConstIterator(nullptr, this);
}

template < typename T >
typename spiridonov::ForwardList< T >::ConstIterator spiridonov::ForwardList< T >::cbegin() const noexcept
{
  return begin();
}
template < typename T >
typename spiridonov::ForwardList< T >::ConstIterator spiridonov::ForwardList< T >::cend() const noexcept
{
  return end();
}

#endif