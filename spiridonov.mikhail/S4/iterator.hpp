#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <functional>
#include <cassert>
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

    const KV_pair & operator*() const
    {
      assert(node_ptr_ != nullptr);
      return node_ptr_->data_;
    }

    const KV_pair * operator->() const
    {
      assert(node_ptr_ != nullptr);
      return std::addressof(node_ptr_->data_);
    }

    iter & operator++()
    {
      assert(node_ptr_ != nullptr);
      if (node_ptr_->right_)
      {
        node_ptr_ = node_ptr_->right_;
        while (node_ptr_->left_)
        {
          node_ptr_ = node_ptr_->left_;
        }
      }
      else
      {
        while (node_ptr_->parent_ && node_ptr_ == node_ptr_->parent_->right_)
        {
          node_ptr_ = node_ptr_->parent_;
        }
        node_ptr_ = node_ptr_->parent_;
      }
      return *this;
    }

    iter & operator++(int)
    {
      assert(node_ptr_ != nullptr);
      iter temp = *this;
      ++(*this);
      return temp;
    }

    iter & operator--()
    {
      assert(node_ptr_ != nullptr);
      if (node_ptr_->left_)
      {
        node_ptr_ = node_ptr_->left_;
        while (node_ptr_->right_)
        {
          node_ptr_ = node_ptr_->right_;
        }
      }
      else
      {
        while (node_ptr_->parent_ && node_ptr_ == node_ptr_->parent_->left_)
        {
          node_ptr_ = node_ptr_->parent_;
        }
        node_ptr_ = node_ptr_->parent_;
      }
      return *this;
    }

    iter & operator--(int)
    {
      assert(node_ptr_ != nullptr);
      iter temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const iter & other) const
    {
      return node_ptr_ == other.node_ptr_;
    }

    bool operator==(const_iter & other) const
    {
      return node_ptr_ == other.node_ptr_;
    }

    bool operator!=(const iter & other) const
    {
      return node_ptr_ != other.node_ptr_;
    }

    bool operator!=(const_iter & other) const
    {
      return node_ptr_ != other.node_ptr_;
    }

  private:
    KV_node * node_ptr_;
    explicit IterT(KV_node * node):
      node_ptr_(node)
    {}
  };
}

#endif
