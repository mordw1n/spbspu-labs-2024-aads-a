#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "t_node.hpp"
#include "const_iterator.hpp"

namespace spiridonov
{
  template< typename Key, typename Value, typename Compare >
  class AVLtree;

  template< typename Key, typename Value, typename Compare >
  class ConstIterT;

  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class IterT
  {
    friend class AVLtree< Key, Value, Compare >;
    friend class ConstIterT< Key, Value, Compare >;
    using KV_pair = std::pair< Key, Value >;
    using const_iter = ConstIterT< Key, Value, Compare >;
    using iter = IterT< Key, Value, Compare >;
    using KV_node = detail::TNode< Key, Value >;

  public:
    IterT():
      node_ptr_(nullptr)
    {}
    ~IterT() = default;

    IterT(const iter &) = default;
    iter & operator=(const iter &) = default;
    IterT(iter && other) noexcept = default;
    iter & operator=(iter && other) noexcept = default;

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

    iter & operator++()
    {
      assert(node_ptr_ != nullptr);
      if (node_->right)
      {
        node_ = node_->right_;
        while (node_->left_)
        {
          node_ = node_->left_;
        }
        return *this;
      }
    }

    iter & operator++(int)
    {
      assert(node_ptr_ != nullptr);
    }

    iter & operator--()
    {
      assert(node_ptr_ != nullptr);
    }

    iter & operator--(int)
    {
      assert(node_ptr_ != nullptr);
    }
  };

}

#endif
