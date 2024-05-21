#ifndef BREADTH_ITERATOR
#define BREADTH_ITERATOR

#include <utility>
#include <iterator>
#include "tree_node.hpp"
#include "queue.hpp"

namespace erohin
{
  template < class Key, class T, class Compare >
  class RedBlackTree;

  template< class Key, class T >
  class BreadthIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    template < class T1, class T2, class T3 >
    friend class RedBlackTree;
  public:
    BreadthIterator();
    BreadthIterator(const BreadthIterator< Key, T > &) = default;
    ~BreadthIterator() = default;
    BreadthIterator< Key, T > & operator=(const BreadthIterator< Key, T > &) = default;
    BreadthIterator< Key, T > & operator++();
    BreadthIterator< Key, T > operator++(int);
    std::pair< Key, T > & operator*();
    const std::pair< Key, T > & operator*() const;
    std::pair< Key, T > * operator->();
    const std::pair< Key, T > * operator->() const;
    bool operator==(const BreadthIterator< Key, T > & rhs) const;
    bool operator!=(const BreadthIterator< Key, T > & rhs) const;
  private:
    detail::Node< Key, T > * node_;
    Queue< detail::Node< Key, T > * > queue_;
    Queue< detail::Node< Key, T > * > layer_queue_;
    explicit BreadthIterator(detail::Node< Key, T > * node_ptr);
  };

  template< class Key, class T >
  BreadthIterator< Key, T >::BreadthIterator():
    node_(nullptr)
  {}

  template< class Key, class T >
  BreadthIterator< Key, T >::BreadthIterator(detail::Node< Key, T > * node_ptr):
    node_(node_ptr)
  {
    queue_.push(node_ptr);
  }

  template< class Key, class T >
  BreadthIterator< Key, T > & BreadthIterator< Key, T >::operator++()
  {
    if (queue_.empty())
    {
      while (!layer_queue_.empty())
      {
        if (layer_queue_.front()->left)
        {
          queue_.push(layer_queue_.front()->left);
        }
        if (layer_queue_.front()->right)
        {
          queue_.push(layer_queue_.front()->right);
        }
        layer_queue_.pop();
      }
      if (queue_.empty())
      {
        node_ = nullptr;
        return *this;
      }
      else
      {
        layer_queue_ = queue_;
      }
    }
    node_ = queue_.front();
    queue_.pop();
    return *this;
  }

  template< class Key, class T >
  BreadthIterator< Key, T > BreadthIterator< Key, T >::operator++(int)
  {
    BreadthIterator< Key, T > temp = *this;
    operator++();
    return temp;
  }

  template< class Key, class T >
  std::pair< Key, T > & BreadthIterator< Key, T>::operator*()
  {
    return node_->data;
  }

  template< class Key, class T >
  const std::pair< Key, T > & BreadthIterator< Key, T>::operator*() const
  {
    return node_->data;
  }

  template< class Key, class T >
  std::pair< Key, T > * BreadthIterator< Key, T >::operator->()
  {
    return std::addressof(node_->data);
  }

  template< class Key, class T >
  const std::pair< Key, T > * BreadthIterator< Key, T >::operator->() const
  {
    return std::addressof(node_->data);
  }

  template< class Key, class T >
  bool BreadthIterator< Key, T >::operator==(const BreadthIterator< Key, T > & rhs) const
  {
    return (node_ == rhs.node_);
  }

  template< class Key, class T >
  bool BreadthIterator< Key, T >::operator!=(const BreadthIterator< Key, T > & rhs) const
  {
    return !(*this == rhs);
  }
}

#endif
