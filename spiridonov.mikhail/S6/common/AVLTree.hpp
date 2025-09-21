#ifndef AVL_TREE_HPP_S4
#define AVL_TREE_HPP_S4

#include "tree.hpp"

namespace spiridonov
{
  template < typename Key, typename Value, typename Compare >
  class AVLTree: protected detail::Tree< Key, Value, Compare >
  {
  public:
    using this_t = AVLTree< Key, Value, Compare >;
    using tree_data_t = typename detail::tree_data_t< Key, Value >;
    using Iterator = typename detail::Tree< Key, Value, Compare >::Iterator;
    using ConstIterator = typename detail::Tree< Key, Value, Compare >::ConstIterator;

    void push(const Key&, const Value&);
    void pop(const Key&);
    Iterator erase(Iterator);
    void erase(Iterator, Iterator);
    Iterator insert(const tree_data_t&);
    template < class InputIterator >
    void insert(InputIterator, InputIterator);
    void insert(std::initializer_list< tree_data_t >);
    template < typename... Args >
    Iterator emplace(const Key&, Args&&...);
    Iterator get(const Key&);
    ConstIterator get(const Key&) const;
    Iterator upperBound(const Key&);
    Iterator lowerBound(const Key&);
    ConstIterator upperBound(const Key&) const;
    ConstIterator lowerBound(const Key&) const;
    bool isEmpty() const noexcept;

    template < typename F >
    F traverseLnr(F) const;
    template < typename F >
    F traverseRnl(F) const;
    template < typename F >
    F traverseBreadth(F) const;

    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

  private:
    using node_t = typename detail::Tree< Key, Value, Compare >::node_t;

    void balanceTree(node_t*);
    void doPop(node_t*);
  };
}

template < typename Key, typename Value, typename Compare >
void spiridonov::AVLTree< Key, Value, Compare >::push(const Key& key, const Value& value)
{
  node_t* new_node = this->doPush(key, value);
  balanceTree(new_node);
}

template < typename Key, typename Value, typename Compare >
void spiridonov::AVLTree< Key, Value, Compare >::pop(const Key& key)
{
  node_t* node_to_delete = this->doSearch(key);
  doPop(node_to_delete);
}

template < typename Key, typename Value, typename Compare >
typename spiridonov::AVLTree< Key, Value, Compare >::Iterator spiridonov::AVLTree< Key, Value, Compare >::erase(Iterator iter)
{
  if (iter == end())
  {
    return iter;
  }
  Iterator return_iter = iter;
  return_iter++;
  pop(iter->first);
  return return_iter;
}
template < typename Key, typename Value, typename Compare >
void spiridonov::AVLTree< Key, Value, Compare >::erase(Iterator first, Iterator last)
{
  while (first != last)
  {
    erase(first++);
  }
}
template < typename Key, typename Value, typename Compare >
typename spiridonov::AVLTree< Key, Value, Compare >::Iterator spiridonov::AVLTree< Key, Value, Compare >::insert(const tree_data_t& data)
{
  node_t* new_node = this->doPush(data.first, data.second);
  balanceTree(new_node);
  return this->getIter(new_node);
}
template < typename Key, typename Value, typename Compare >
template < class InputIterator >
void spiridonov::AVLTree< Key, Value, Compare >::insert(InputIterator first, InputIterator last)
{
  while (first != last)
  {
    insert({*(first++), *(first++)});
  }
}
template < typename Key, typename Value, typename Compare >
void spiridonov::AVLTree< Key, Value, Compare >::insert(std::initializer_list< tree_data_t > il)
{
  for (auto&& data: il)
  {
    insert(data);
  }
}

template < typename Key, typename Value, typename Compare >
template < typename... Args >
typename spiridonov::AVLTree< Key, Value, Compare >::Iterator spiridonov::AVLTree< Key, Value, Compare >::emplace(const Key& key, Args&&... args)
{
  return insert({key, Value(std::forward< Args >(args)...)});
}

template < typename Key, typename Value, typename Compare >
typename spiridonov::AVLTree< Key, Value, Compare >::Iterator spiridonov::AVLTree< Key, Value, Compare >::get(const Key& key)
{
  return this->doGet(key);
}

template < typename Key, typename Value, typename Compare >
typename spiridonov::AVLTree< Key, Value, Compare >::ConstIterator spiridonov::AVLTree< Key, Value, Compare >::get(const Key& key) const
{
  return this->doGet(key);
}

template < typename Key, typename Value, typename Compare >
bool spiridonov::AVLTree< Key, Value, Compare >::isEmpty() const noexcept
{
  return detail::Tree< Key, Value, Compare >::isEmpty();
}

template < typename Key, typename Value, typename Compare >
void spiridonov::AVLTree< Key, Value, Compare >::balanceTree(node_t* node)
{
  if (this->isNil(node))
  {
    return;
  }

  if (this->getHeight(node->right_) > this->getHeight(node->left_) && !this->isNil(node->right_))
  {
    if (this->getHeight(node->right_->left_) <= this->getHeight(node->right_->right_))
    {
      this->rotateSmallLeft(node->right_);
    }
    else if (!this->isNil(node->right_->left_))
    {
      if (this->getHeight(node->right_->left_) > this->getHeight(node->right_->right_))
      {
        this->rotateBigLeft(node->right_->left_);
      }
    }
  }
  else if (this->getHeight(node->left_) > this->getHeight(node->right_) && !this->isNil(node->left_))
  {
    if (this->getHeight(node->left_->right_) <= this->getHeight(node->left_->left_))
    {
      this->rotateSmallRight(node->left_);
    }
    else if (!this->isNil(node->left_->right_))
    {
      if (this->getHeight(node->left_->right_) > this->getHeight(node->left_->left_))
      {
        this->rotateBigRight(node->left_->right_);
      }
    }
  }

  balanceTree(node->parent_);
}

template < typename Key, typename Value, typename Compare >
typename spiridonov::AVLTree< Key, Value, Compare >::Iterator spiridonov::AVLTree< Key, Value, Compare >::upperBound(const Key& key)
{
  return const_cast< const this_t& >(*this).upperBound(key);
}
template < typename Key, typename Value, typename Compare >
typename spiridonov::AVLTree< Key, Value, Compare >::Iterator spiridonov::AVLTree< Key, Value, Compare >::lowerBound(const Key& key)
{
  return const_cast< const this_t& >(*this).lowerBound(key);
}
template < typename Key, typename Value, typename Compare >
typename spiridonov::AVLTree< Key, Value, Compare >::ConstIterator spiridonov::AVLTree< Key, Value, Compare >::upperBound(const Key& key) const
{
  return detail::Tree< Key, Value, Compare >::upperBound(key);
}
template < typename Key, typename Value, typename Compare >
typename spiridonov::AVLTree< Key, Value, Compare >::ConstIterator spiridonov::AVLTree< Key, Value, Compare >::lowerBound(const Key& key) const
{
  return detail::Tree< Key, Value, Compare >::lowerBound(key);
}

template < typename Key, typename Value, typename Compare >
void spiridonov::AVLTree< Key, Value, Compare >::doPop(node_t* node)
{
  if (this->isNil(node))
  {
    return;
  }
  if (!this->isHasChild(node))
  {
    if (node == this->root_)
    {
      this->root_ = this->nil_;
      delete node;
    }
    else if (this->isLeft(node))
    {
      node_t* node_to_balance = node->parent_;
      node->parent_->left_ = this->nil_;
      delete node;
      balanceTree(node_to_balance);
    }
    else if (this->isRight(node))
    {
      node_t* node_to_balance = node->parent_;
      node->parent_->right_ = this->nil_;
      delete node;
      balanceTree(node_to_balance);
    }
    return;
  }
  node_t* right_min = this->getMin(node->right_);
  if (!this->isNil(right_min))
  {
    node_t* node_to_balance = right_min->parent_;
    std::swap(right_min->data_, node->data_);
    doPop(right_min);
    balanceTree(node_to_balance);
  }
  else
  {
    node_t* left_max = this->getMax(node->left_);
    node_t* node_to_balance = left_max->parent_;
    std::swap(left_max->data_, node->data_);
    doPop(left_max);
    balanceTree(node_to_balance);
  }
}

template < typename Key, typename Value, typename Compare >
template < typename F >
F spiridonov::AVLTree< Key, Value, Compare >::traverseLnr(F f) const
{
  return detail::Tree< Key, Value, Compare >::traverseLnr(f);
}

template < typename Key, typename Value, typename Compare >
template < typename F >
F spiridonov::AVLTree< Key, Value, Compare >::traverseRnl(F f) const
{
  return detail::Tree< Key, Value, Compare >::traverseRnl(f);
}

template < typename Key, typename Value, typename Compare >
template < typename F >
F spiridonov::AVLTree< Key, Value, Compare >::traverseBreadth(F f) const
{
  return detail::Tree< Key, Value, Compare >::traverseBreadth(f);
}

template < typename Key, typename Value, typename Compare >
typename spiridonov::AVLTree< Key, Value, Compare >::Iterator spiridonov::AVLTree< Key, Value, Compare >::begin() noexcept
{
  return cbegin();
}

template < typename Key, typename Value, typename Compare >
typename spiridonov::AVLTree< Key, Value, Compare >::Iterator spiridonov::AVLTree< Key, Value, Compare >::end() noexcept
{
  return cend();
}

template < typename Key, typename Value, typename Compare >
typename spiridonov::AVLTree< Key, Value, Compare >::ConstIterator spiridonov::AVLTree< Key, Value, Compare >::begin() const noexcept
{
  return cbegin();
}

template < typename Key, typename Value, typename Compare >
typename spiridonov::AVLTree< Key, Value, Compare >::ConstIterator spiridonov::AVLTree< Key, Value, Compare >::end() const noexcept
{
  return cend();
}

template < typename Key, typename Value, typename Compare >
typename spiridonov::AVLTree< Key, Value, Compare >::ConstIterator spiridonov::AVLTree< Key, Value, Compare >::cbegin() const noexcept
{
  return detail::Tree< Key, Value, Compare >::cbegin();
}

template < typename Key, typename Value, typename Compare >
typename spiridonov::AVLTree< Key, Value, Compare >::ConstIterator spiridonov::AVLTree< Key, Value, Compare >::cend() const noexcept
{
  return detail::Tree< Key, Value, Compare >::cend();
}

#endif
