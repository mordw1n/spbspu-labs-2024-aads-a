#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <algorithm>
#include <iostream>
#include "t_node.hpp"

namespace spiridonov
{
  template< class Key, class Value, class Compare = std::less< Key > >
  struct AVLtree
  {
  public:
    AVLtree();
    AVLtree(const AVLtree& other);
    AVLtree(AVLtree&& other) noexcept;
    //~AVLtree();

  private:
    using KV_tnode = detail::TNode< Key, Value >;
    using KVC_AVLtree = AVLtree< Key, Value, Compare >;

    size_t size_;
    KV_tnode* root_;
    Compare comp_;

    KV_tnode* insert(KV_tnode* root_, const Key& key_, const Value& value_);
    KV_tnode* erase(KV_tnode* node_, const Key& key_);
    KV_tnode* search(KV_tnode* node_, const Key& key_, const Value& value_);
    KV_tnode* balance(KV_tnode* root_);

    void clear();
    int height(KV_tnode* root_);
    int get_balance_f(KV_tnode* root_);

    template< typename Key, typename Value, typename Compare >
    AVLtree():
      size_(0),
      root_(nullptr),
      comp_(Compare())
    {}

    template< typename Key, typename Value, typename Compare >
    AVLtree(const AVLtree& other):
      size_(0),
      root_(nullptr),
      comp_(other.comp_)
    {
      try
      {
        for (auto it = other.cbegin(); it != other.cend(); ++it)
        {
          push(it->first, it->second);
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }

    template< typename Key, typename Value, typename Compare >
    AVLtree(AVLtree&& other) noexcept:
      size_(other.size_),
      root_(other.root_),
      comp_(other.comp_)
    {
      other.size_ = 0;
      other.root_ = nullptr;
    }

    ~AVLtree()
    {
      clear();
    }

    template< typename Key, typename Value, typename Compare >
    void clear()
    {
      while (root_ != nullptr)
      {
        root_ = erase(root_, root_->data_.first);
      }
      size_ = 0;
    }

    KV_tnode* rotation_R(KV_tnode* root_)
    {
      KV_tnode* new_root = root_->left_;
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

    KV_tnode* rotation_L(KV_tnode* root_)
    {
      KV_tnode* new_root = root_->right_;
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

    KV_tnode* rotation_LR(KV_tnode* root_)
    {
      root_->left_ = rotation_L(root_->left_);
      return rotation_R(root_);
    }

    KV_tnode* rotation_RL(KV_tnode* root_)
    {
      root_->right_ = rotation_R(root_->right_);
      return rotation_L(root_);
    }

    template< typename Key, typename Value, typename Compare >
    KV_tnode* insert(KV_tnode* root_, const Key& key_, const Value& value_)
    {
      if (root_ == nullptr)
      {
        KVC_AVLtree* new_node = nullptr;
        try
        {
          new_node = new KVC_AVLtree;
          new_node->data_ = std::make_pair(key_, value_);
          new_node->left_ = nullptr;
          new_node->right_ = nullptr;
          new_node->parent_ = nullptr;
        }
        catch (...)
        {
          delete new_node;
          throw;
        }
        return new_node;
      }
      else if (comp_(key_, root_->data_.first))
      {
        root_->left_ = insert(root_->left_, key_, value_);
        root_->left_->parent_ = root_;
      }
      else if (comp_(root_->data_.first, key_))
      {
        root_->right_ = insert(root_->right_, key_, value_);
        root_->right_->parent_ = root_;
      }
      else
      {
        root_->data_.second = value_;
      }

      balance(root_);
      return root_;
    }

    KVC_AVLtree* search(KVC_AVLtree* root_, const Key& key_)
    {
      if (root_ == nullptr || root_->data_.first == key_)
      {
        return root_;
      }
      if (comp_(key_, root_->data_.first))
      {
        return search(root_->left_, key_);
      }
      return search(root_->right_, key_);
    }

    KVC_AVLtree* erase(KVC_AVLtree* root_, const Key& key_)
    {
      if (root_ == nullptr)
      {
        return root_;
      }

      if (comp_(key_, root_->data_.first))
      {
        root_->left_ = erase(root_->left_, key_);
      }
      else if (comp_(root_->data_.first, key_))
      {
        root_->right_ = erase(root_->right_, key_);
      }
      else
      {
        if (root_->left_ == nullptr)
        {
          KVC_AVLtree* temp = root_->right_;
          delete root_;
          return temp;
        }
        else if (root_->right_ == nullptr)
        {
          KVC_AVLtree* temp = root_->left_;
          delete root_;
          return temp;
        }

        KVC_AVLtree* temp = leftmost(root_->right_);
        root_->data_ = temp->data_;
        root_->right_ = erase(root_->right_, temp->data_.first);
      }
      //return balance(root_);
      return root_;
    }

    KVC_AVLtree* leftmost(KVC_AVLtree* root_)
    {
      while (root_ && root_->left_ != nullptr)
      {
        root_ = root_->left_;
      }
      return root_;
    }

    KVC_AVLtree* rightmost(KVC_AVLtree* root_)
    {
      while (root_ && root_->right_ != nullptr)
      {
        root_ = root_->rightmost;
      }
      return root_;
    }

  };
}

#endif
