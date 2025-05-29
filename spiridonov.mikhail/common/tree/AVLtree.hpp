#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <algorithm>
#include <iostream>
#include "t_node.hpp"
#include "iterator.hpp"
#include "const_iterator.hpp"
//#include "tree/t_node.hpp"
//#include "tree/iterator.hpp"
//#include "tree/const_iterator.hpp"

namespace spiridonov
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
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
      AVLtree()
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
      size_(0),
      root_(other.root_)
    {
      other.root_ = nullptr;
      other.size_ = 0;
    }

    ~AVLtree()
    {
      clear();
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

    Value& operator[](const Key& key)
    {
      KV_node* node_ = search(root_, key);
      if (!node_)
      {
        root_ = insert(root_, key, Value());
        node_ = search(root_, key);
      }
      return node_->data_.second;
    }

    const Value& operator[](const Key& key) const
    {
      KV_node* node_ = search(root_, key);
      if (node_)
      {
        return node_->data_.second;
      }
      else
      {
        throw std::out_of_range("There is no key");
      }
    }

    template < typename F >
    F traverse_lnr(F f)
    {

    }

    template < typename F >
    F traverse_lnr(F f) const
    {

    }

    template < typename F >
    F traverse_rnl(F f)
    {

    }

    template < typename F >
    F traverse_rnl(F f) const
    {

    }

    template < typename F >
    F traverse_breadth(F f)
    {

    }

    template < typename F >
    F traverse_breadth(F f) const
    {

    }

    Value& at(const Key& key)
    {
      KV_node* node_ = get_root(root_, key);
      if (node_)
      {
        return node_->data_.second;
      }
      else
      {
        throw std::out_of_range("Key not found");
      }
    }

    const Value& at(const Key& key) const
    {
      KV_node* node_ = get_root(root_, key);
      if (node_)
      {
        return node_->data_.second;
      }
      else
      {
        throw std::out_of_range("Key not found");
      }
    }

    void swap(AVLtree& other) noexcept
    {
      static_assert(std::is_nothrow_copy_constructible< Compare >::value);
      std::swap(root_, other.root_);
      std::swap(size_, other.size_);
      std::swap(comp_, other.comp_);
    }

    void push_cmd(const Key& key, const Value& value)
    {
      root_ = insert(root_, key, value);
      ++size_;
    }

    iter find(const Key& key)
    {
      KV_node* current = root_;
      while (current)
      {
        if (current->data_.first == key)
        {
          return iter(current);
        }
        else if (comp_(current->data_.first, key))
        {
          current = current->right_;
        }
        else
        {
          current = current->left_;
        }
      }
      return end();
    }

    const_iter find(const Key& key) const
    {
      KV_node* current = root_;
      while (current)
      {
        if (current->data_.first == key)
        {
          return const_iter(current);
        }
        else if (comp_(current->data_.first, key))
        {
          current = current->right_;
        }
        else
        {
          current = current->left_;
        }
      }
      return cend();
    }

    std::pair< iter, iter > equal_range(const Key& key)
    {
      iter it = find(key);
      if (it == end())
      {
        return std::make_pair(end(), end());
      }
      iter next = it;
      ++next;
      return std::make_pair(it, next);
    }

    std::pair< const_iter, const_iter > equal_range(const Key& key) const
    {
      const_iter it = find(key);
      if (it == cend())
      {
        return std::make_pair(cend(), cend());
      }
      const_iter next = it;
      ++next;
      return std::make_pair(it, next);
    }

    size_t size(KV_node* node_)
    {
      return (node_ == nullptr) ? 0 : node_->size_;
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

    bool empty() const noexcept
    {
      return size_ == 0;
    }

    bool contains(const Key& key) const
    {
      return get_root(root_, key) != nullptr;
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

    const Value& get_root(const Key& key) const
    {
      KV_node* val = get_root(key, root_);
      return val->data_.second;
    }

    KV_node* get_root(KV_node* node_, const Key& key) const
    {
      if (node_ == nullptr || (!comp_(key, node_->data_.first) && !comp_(node_->data_.first, key)))
      {
        return node_;
      }
      if (comp_(key, node_->data_.first))
      {
        return get_root(node_->left_, key);
      }
      else
      {
        return get_root(node_->right_, key);
      }
    }

    Value& get_root(const Key& key)
    {
      KV_node* val = get_root(key, root_);
      return val->data_.second;
    }

    KV_node* get_root(KV_node* node_, const Key& key)
    {
      if (node_ == nullptr || node_->data_.first == key)
      {
        return node_;
      }
      if (comp_(key, node_->data_.first))
      {
        return get_root(node_->left_, key);
      }
      else
      {
        return get_root(node_->right_, key);
      }
    }

    KV_node* search(KV_node* root_, const Key& key)
    {
      while (root_ != nullptr)
      {
        if (root_->data_.first == key)
        {
          return root_;
        }
        root_ = comp_(key, root_->data_.first) ? root_->left_ : root_->right_;
      }
      return nullptr;
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
          --size_;
          return temp;
        }
        else if (root_->right_ == nullptr)
        {
          KV_node* temp = root_->left_;
          delete root_;
          --size_;
          return temp;
        }

        KV_node* temp = leftmost(root_->right_);
        root_->data_ = temp->data_;
        root_->right_ = erase(root_->right_, temp->data_.first);
      }
      return balance(root_);
    }

    int height(KV_node* node_)
    {
      if (node_ == nullptr)
      {
        return 0;
      }
      return std::max(height(node_->left_), height(node_->right_)) + 1;
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

      if (balance_factor > 1)
      {
        if (height(root_->left_->left_) >= height(root_->left_->right_))
        {
          return rotation_RR(root_);
        }
        else
        {
          return rotation_LR(root_);
        }
      }
      else if (balance_factor < -1)
      {
        if (height(root_->right_->right_) >= height(root_->right_->left_))
        {
          return rotation_LL(root_);
        }
        else
        {
          return rotation_RL(root_);
        }
      }
      return root_;
    }

    KV_node* leftmost(KV_node* node_) const
    {
      if (node_ == nullptr)
      {
        return nullptr;
      }
      while (node_->left_ != nullptr)
      {
        node_ = node_->left_;
      }
      return node_;
    }
  };
}

#endif