#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <algorithm>
#include <iostream>
#include "t_node.hpp"
#include "iterator.hpp"
#include "const_iterator.hpp"

namespace spiridonov
{
  template< class Key, class Value, class Compare = std::less< Key > >
  class AVLtree
  {
  public:
    using KV_node = detail::TNode< Key, Value >;
    using KVC_AVLtree = AVLtree< Key, Value, Compare >;
    using iter = IterT< Key, Value, Compare >;
    using const_iter = ConstIterT< Key, Value, Compare >;

    KV_node* root_;
    size_t size_;

    AVLtree():
      root_(nullptr),
      size_(0)
    {}

    AVLtree(const AVLtree& other):
      root_(nullptr),
      size_(0)
    {
      try
      {
        for (auto it = other.cbegin(); it != other.cend(); ++it)
        {
          insert(it->first, it->second);
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }

    AVLtree(AVLtree&& other) noexcept:
      root_(other.root_)
    {
      other.root_ = nullptr;
      other.size_ = 0;
    }

    AVLtree& operator=(const AVLtree& other)
    {
      if (this != &other)
      {
        clear();
        size_ = 0;
        try
        {
          for (auto it = other.cbegin(); it != other.cend(); ++it)
          {
            insert(it->first, it->second);
          }
        }
        catch (...)
        {
          clear();
          throw;
        }
      }
      return *this;
    }

    AVLtree& operator=(AVLtree&& other) noexcept
    {
      if (this != &other)
      {
        clear();
        root_ = other.root_;
        size_ = other.size_;
        other.root_ = nullptr;
        other.size_ = 0;
      }
      return *this;
    }

    ~AVLtree()
    {
      clear();
    }

    void insert(const Key& key, const Value value)
    {
      root_ = insert(root_, key, value);
    }

    KV_node* erase(const Key& key)
    {
      root_ = erase(root_, key);
      return root_;
    }

    iter begin()
    {
      return iter(leftmost(root_));
    }

    iter end()
    {
      return iter(nullptr);
    }

    const_iter cbegin() const
    {
      return const_iter(leftmost(root_));
    }

    const_iter cend() const
    {
      return const_iter(nullptr);
    }

  private:
    Compare comp_;

    void clear()
    {
      while (root_ != nullptr)
      {
        root_ = erase(root_, root_->data_.first);
      }
      size_ = 0;
    }

    KV_node* rotation_RR(KV_node* root_)
    {
      KV_node* new_root = root_->left_;
      root_->left_ = new_root->right_;
      if (new_root->right_ != nullptr)
      {
        new_root->right_->parent_ = root_;
      }
      new_root->right_ = root_;
      new_root->parent_ = root_->parent_;
      root_->parent_ = new_root;
      return new_root;
    }

    KV_node* rotation_LL(KV_node* root_)
    {
      KV_node* new_root = root_->right_;
      root_->right_ = new_root->left_;
      if (new_root->left_ != nullptr)
      {
        new_root->left_->parent_ = root_;
      }
      new_root->left_ = root_;
      new_root->parent_ = root_->parent_;
      root_->parent_ = new_root;
      return new_root;
    }

    KV_node* rotation_LR(KV_node* root_)
    {
      root_->left_ = rotation_LL(root_->left_);
      return rotation_RR(root_);
    }

    KV_node* rotation_RL(KV_node* root_)
    {
      root_->right_ = rotation_RR(root_->right_);
      return rotation_LL(root_);
    }

    KV_node* insert(KV_node* root_, const Key& key, const Value& value)
    {
      if (root_ == nullptr)
      {
        KV_node* new_node = nullptr;
        try
        {
          new_node = new KV_node;
          new_node->data_ = std::make_pair(key, value);
          new_node->left_ = nullptr;
          new_node->right_ = nullptr;
          new_node->parent_ = nullptr;
        }
        catch (...)
        {
          delete new_node;
          throw;
        }
        ++size_;
        return new_node;
      }
      else if (comp_(key, root_->data_.first))
      {
        root_->left_ = insert(root_->left_, key, value);
        root_->left_->parent_ = root_;
      }
      else if (comp_(root_->data_.first, key))
      {
        root_->right_ = insert(root_->right_, key, value);
        root_->right_->parent_ = root_;
      }
      else
      {
        root_->data_.second = value;
        return root_;
      }
      return balance(root_);
    }

    KV_node* search(KV_node* root_, const Key& key)
    {
      if (root_ == nullptr || root_->data_.first == key)
      {
        return root_;
      }
      if (comp_(key, root_->data_.first))
      {
        return search(root_->left_, key);
      }
      return search(root_->right_, key);
    }

    KV_node* erase(KV_node* root_, const Key& key)
    {
      if (root_ == nullptr)
      {
        return root_;
      }

      if (comp_(key, root_->data_.first))
      {
        root_->left_ = erase(root_->left_, key);
      }
      else if (comp_(root_->data_.first, key))
      {
        root_->right_ = erase(root_->right_, key);
      }
      else
      {
        if (root_->left_ == nullptr)
        {
          KV_node* temp = root_->right_;
          delete root_;
          return temp;
        }
        else if (root_->right_ == nullptr)
        {
          KV_node* temp = root_->left_;
          delete root_;
          return temp;
        }

        KV_node* temp = leftmost(root_->right_);
        root_->data_ = temp->data_;
        root_->right_ = erase(root_->right_, temp->data_.first);
      }
      return balance(root_);
    }

    int height(KV_node* node)
    {
      if (node == nullptr)
      {
        return 0;
      }
      int left_height = height(node->left_);
      int right_height = height(node->right_);
      return std::max(left_height, right_height) + 1;
    }

    KV_node* balance(KV_node* root_)
    {
      if (root_ == nullptr)
      {
        return nullptr;
      }

      int left_height = height(root_->left_);
      int right_height = height(root_->right_);
      int balance_factor = left_height - right_height;

      if (balance_factor > 1 && height(root_->left_->left_) >= height(root_->left_->right_))
      {
        return rotation_RR(root_);
      }

      if (balance_factor > 1 && height(root_->left_->left_) < height(root_->left_->right_))
      {
        return rotation_LR(root_);
      }

      if (balance_factor < -1 && height(root_->right_->right_) >= height(root_->right_->left_))
      {
        return rotation_LL(root_);
      }

      if (balance_factor < -1 && height(root_->right_->right_) < height(root_->right_->left_))
      {
        return rotation_RL(root_);
      }
      return root_;
    }

    KV_node* leftmost(KV_node* node) const
    {
      if (node == nullptr)
      {
        return nullptr;
      }
      while (node->left_ != nullptr)
      {
        node = node->left_;
      }
      return node;
    }
  };
}

#endif
