#ifndef ITERATOR_HPP
#define ITERATOR_HPP

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
      if (node_ptr_->right)
      {
        node_ptr_ = node_ptr_->right;
        while (node_ptr_->left)
        {
          node_ptr_ = node_ptr_->left;
        }
      }
      else
      {
        while (node_ptr_->parent && node_ptr_ == node_ptr_->parent->right)
        {
          node_ptr_ = node_ptr_->parent;
        }
        node_ptr_ = node_ptr_->parent;
      }
      return *this;
    }

    iter & operator++(int)
    {
      iter temp = *this;
      ++(*this);
      return temp;
    }

    iter & operator--()
    {
      assert(node_ptr_ != nullptr);
      if (node_ptr_->left)
      {
        node_ptr_ = node_ptr_->left;
        while (node_ptr_->right)
        {
          node_ptr_ = node_ptr_->right;
        }
      }
      else
      {
        while (node_ptr_->parent && node_ptr_ == node_ptr_->parent->left)
        {
          node_ptr_ = node_ptr_->parent;
        }
        node_ptr_ = node_ptr_->parent;
      }
      return *this;
    }

    iter & operator--(int)
    {
      iter temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const iter & other) const
    {
      return node_ptr_ == other.node_;
    }

    bool operator==(const_iter & other) const
    {
      return node_ptr_ == other.node_;
    }

    bool operator!=(const iter& other) const
    {
      return node_ptr_ != other.node_;
    }

    bool operator!=(const_iter& other) const
    {
      return node_ptr_ != other.node_;
    }

  private:
    KV_node * node_;
    explicit IterT(KV_node* node):
      node_(node)
    {}
  };
}

#endif
