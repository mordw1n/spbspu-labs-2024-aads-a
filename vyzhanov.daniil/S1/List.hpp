#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "node.hpp"
#include "iterator.hpp"
#include "const_iterator.hpp"

namespace vyzhanov
{
  template<typename T>
  struct List
  {
    using citerator = ConstBiIterator< T >;
    using iterator = BiIterator< T >;

    List();
    ~List();

    void clear();
    bool empty();
    void push_back(const T&);
    void push_back(T&&);
    void push_front(const T&);
    void push_front(T&&);

    iterator begin() noexcept;
    citerator cbegin() const noexcept;
    iterator end() noexcept;
    citerator cend() const noexcept;
  private:
    Node<T>* head_;
    Node<T>* tail_;
    size_t size_;
  };

  template< class T >
  List< T >::List() :
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template< class T >
  List< T >::~List()
  {
    clear();
  }

  template < typename T>
  void List<T>::clear()
  {
    while (head_ != tail_)
    {
      Node< T >* newHead = head_->next_;
      delete head_;
      head_ = newHead;
    }
  }

  template < typename T>
  bool List<T>::empty()
  {
    return (head_ = tail_);
  }

  template < typename T>
  void List<T>::push_back(const T& data)
  {
    Node< T >* newNode = new Node< T >(data, nullptr, tail_);
    newNode->prev_ = tail_;
    if (head_ == nullptr)
    {
      head_ = newNode;
    }
    else
    {
      tail_->next_ = newNode;
    }
    tail_ = newNode;
    ++size_;
  }

  template < typename T>
  void List<T>::push_back(T&& data)
  {
    Node< T >* newNode = new Node< T >(std::move(data), nullptr, tail_);
    newNode->prev_ = tail_;
    if (head_ == nullptr)
    {
      head_ = newNode;
    }
    else
    {
      tail_->next_ = newNode;
    }
    tail_ = newNode;
    ++size_;
  }

  template < typename T>
  void List<T>::push_front(const T& data)
  {
    Node< T >* newNode = new Node< T >(data, head_, nullptr);
    newNode->next_ = head_;
    if (head_ == nullptr)
    {
      head_ = newNode;
    }
    else
    {
      head_->prev_ = newNode;
    }
    head_ = newNode;
    ++size_;
  }

  template < typename T>
  void List<T>::push_front(T&& data)
  {
    Node< T >* newNode = new Node< T >(std::move(data), nullptr, tail_);
    newNode->next_ = head_;
    if (head_ == nullptr)
    {
      head_ = newNode;
    }
    else
    {
      head_->next_ = newNode;
    }
    head_ = newNode;
    ++size_;
  }

  template < typename T>
  BiIterator<T> List<T>::begin() noexcept
  {
    return iterator(head_);
  }

  template< typename T >
  ConstBiIterator< T > List< T >::cbegin() const noexcept
  {
    return citerator(head_);
  }

  template < typename T>
  BiIterator<T> List<T>::end() noexcept
  {
    return iterator(tail_);
  }

  template< typename T >
  ConstBiIterator< T > List< T >::cend() const noexcept
  {
    return citerator(tail_);
  }
}
#endif
