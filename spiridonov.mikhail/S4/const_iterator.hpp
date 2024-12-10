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

    const_iter & operator++()
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

    const_iter & operator++(int)
    {
      assert(node_ptr_ != nullptr);
      iter temp = *this;
      ++(*this);
      return temp;
    }

    const_iter & operator--()
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

    const_iter & operator--(int)
    {
      assert(node_ptr_ != nullptr);
      const_iter temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const const_iter & other) const
    {
      return node_ptr_ == other.node_ptr_;
    }

    bool operator==(iter & other) const
    {
      return node_ptr_ == other.node_ptr_;
    }

    bool operator!=(const const_iter & other) const
    {
      return node_ptr_ != other.node_ptr_;
    }

    bool operator!=(iter & other) const
    {
      return node_ptr_ != other.node_ptr_;
    }

  private:
    const KV_node * node_ptr_;
    explicit ConstIterT(KV_node * node):
      node_ptr_(node)
    {}
  };
}

#endif
