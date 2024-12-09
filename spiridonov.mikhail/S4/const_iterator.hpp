#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include "t_node.hpp"
#include "iterator.hpp"

namespace spiridonov
{
  template< typename Key, typename Value, typename Compare >
  class AVLtree;

  template< typename Key, typename Value, typename Compare >
  class IterT;

  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class ConstIterT
  {
    friend class AVLtree< Key, Value, Compare >;
    friend class IterT< Key, Value, Compare >;
    using KV_pair = std::pair< Key, Value >;
    using const_iter  = ConstIterT< Key, Value, Compare >;
    using iter = IterT< Key, Value, Compare >;
    using KV_node = detail::TNode< Key, Value >;

  public:
    ConstIterT():
      node_ptr_(nullptr)
    {}
    ~ConstIterT() = default;

    ConstIterT(const const_iter &) = default;
    const_iter & operator=(const const_iter &) = default;
    ConstIterT(const_iter && other) noexcept = default;
    const_iter & operator=(const_iter && other) noexcept = default;

    KV_pair & operator*()
    {
      assert(node_ptr_ != nullptr);
      return node_ptr_->data_;
    }

    KV_pair * operator->()
    {
      assert(node_ptr_ != nullptr);
      return std::addressof(node_ptr_->data_)
    }

    const_iter & operator++()
    {
      assert(node_ptr_ != nullptr);
    }

    const_iter & operator++(int)
    {
      assert(node_ptr_ != nullptr);
    }

    const_iter & operator--()
    {
      assert(node_ptr_ != nullptr);
    }

    const_iter & operator--(int)
    {
      assert(node_ptr_ != nullptr);
    }
  };

}

#endif
