#ifndef TREE_HPP_S4
#define TREE_HPP_S4

#include <cassert>
#include <stdexcept>
#include <cmath>
#include "queue.hpp"
#include "stack.hpp"

namespace spiridonov
{
  namespace detail
  {
    template < typename Key, typename Value >
    using tree_data_t = std::pair< Key, Value >;
    template < typename Key, typename Value >
    struct TreeNode
    {
      tree_data_t< Key, Value > data_;
      TreeNode* left_;
      TreeNode* right_;
      TreeNode* parent_;
    };
    template < typename Key, typename Value, typename Compare, typename Node = TreeNode< Key, Value > >
    class Tree
    {
    public:
      class Iterator;
      class ConstIterator;
      using this_t = Tree;

      Tree();
      Tree(const this_t&);
      Tree(this_t&&) noexcept;
      ~Tree();

      this_t& operator=(const this_t&);
      this_t& operator=(this_t&&) noexcept;

      void swap(this_t&) noexcept;
      void push(const Key&, const Value&);
      template < typename... Args >
      Iterator emplace(const Key&, Args&&...);
      Iterator get(const Key&);
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

    protected:
      using node_t = Node;
      node_t* nil_;
      node_t* root_;

      void clear(node_t*);
      void add(node_t*, node_t*, node_t*);
      void rotateSmallLeft(node_t*);
      void rotateSmallRight(node_t*);
      void rotateBigLeft(node_t*);
      void rotateBigRight(node_t*);

      bool isNil(node_t*) const;
      bool isLeftOutside(node_t*) const;
      bool isLeft(node_t*) const;
      bool isRight(node_t*) const;
      bool isHasParent(node_t*) const;
      bool isHasGrandParent(node_t*) const;
      bool isHasUncle(node_t*) const;
      bool isHasChild(node_t*) const;

      const Key& getKey(const node_t*) const;
      size_t getHeight(node_t*) const;

      const node_t* doSearch(const Key&) const;
      node_t* doSearch(const Key&);
      node_t* doPush(const Key&, const Value&);
      ConstIterator doGet(const Key&) const;
      ConstIterator getIter(node_t*) const;

      node_t* getMin(node_t*) const;
      node_t* getMax(node_t*) const;
      node_t* getParent(node_t*) const;
      node_t* getGrandParent(node_t*) const;
      node_t* getUncle(node_t*) const;

      node_t* getNext(node_t*) const;
      node_t* getPrev(node_t*) const;
    };
  }
  template < typename Key, typename Value, typename Compare, typename Node >
  using tree_data_t = typename spiridonov::detail::tree_data_t< Key, Value >;
  template < typename Key, typename Value, typename Compare, typename Node >
  using tree_iter_t = typename spiridonov::detail::Tree< Key, Value, Compare, Node >::Iterator;
  template < typename Key, typename Value, typename Compare, typename Node >
  using tree_citer_t = typename spiridonov::detail::Tree< Key, Value, Compare, Node >::ConstIterator;
}

template < typename Key, typename Value, typename Compare, typename Node >
class spiridonov::detail::Tree< Key, Value, Compare, Node >::Iterator
{
public:
  friend class Tree;
  using this_t = Iterator;
  using tree_data_t = spiridonov::tree_data_t< Key, Value, Compare, Node >;

  Iterator();
  Iterator(const this_t&) = default;
  Iterator(ConstIterator);
  ~Iterator() = default;
  this_t& operator=(const this_t&) = default;

  tree_iter_t< Key, Value, Compare, Node >& operator++();
  tree_iter_t< Key, Value, Compare, Node > operator++(int);
  tree_iter_t< Key, Value, Compare, Node >& operator--();
  tree_iter_t< Key, Value, Compare, Node > operator--(int);

  tree_data_t& operator*();
  tree_data_t* operator->();
  const tree_data_t& operator*() const;
  const tree_data_t* operator->() const;

  bool operator!=(const this_t&) const;
  bool operator==(const this_t&) const;

private:
  ConstIterator iter_;
};
template < typename K, typename V, typename C, typename N >
spiridonov::detail::Tree< K, V, C, N >::Iterator::Iterator():
  iter_()
{}
template < typename K, typename V, typename C, typename N >
spiridonov::detail::Tree< K, V, C, N >::Iterator::Iterator(ConstIterator iter):
  iter_(iter)
{}
template < typename K, typename V, typename C, typename N >
typename spiridonov::tree_iter_t< K, V, C, N >& spiridonov::detail::Tree< K, V, C, N >::Iterator::operator++()
{
  iter_++;
  return *this;
}
template < typename K, typename V, typename C, typename N >
typename spiridonov::tree_iter_t< K, V, C, N > spiridonov::detail::Tree< K, V, C, N >::Iterator::operator++(int)
{
  return Iterator(iter_++);
}
template < typename K, typename V, typename C, typename N >
typename spiridonov::tree_iter_t< K, V, C, N >& spiridonov::detail::Tree< K, V, C, N >::Iterator::operator--()
{
  iter_--;
  return *this;
}
template < typename K, typename V, typename C, typename N >
typename spiridonov::tree_iter_t< K, V, C, N > spiridonov::detail::Tree< K, V, C, N >::Iterator::operator--(int)
{
  return Iterator(iter_--);
}
template < typename K, typename V, typename C, typename N >
typename spiridonov::tree_data_t< K, V, C, N >& spiridonov::detail::Tree< K, V, C, N >::Iterator::operator*()
{
  return const_cast< tree_data_t& >(*iter_);
}
template < typename K, typename V, typename C, typename N >
typename spiridonov::tree_data_t< K, V, C, N >* spiridonov::detail::Tree< K, V, C, N >::Iterator::operator->()
{
  return std::addressof(const_cast< tree_data_t& >(*iter_));
}
template < typename K, typename V, typename C, typename N >
const typename spiridonov::tree_data_t< K, V, C, N >& spiridonov::detail::Tree< K, V, C, N >::Iterator::operator*() const
{
  return *iter_;
}
template < typename K, typename V, typename C, typename N >
const typename spiridonov::tree_data_t< K, V, C, N >* spiridonov::detail::Tree< K, V, C, N >::Iterator::operator->() const
{
  return std::addressof(*iter_);
}
template < typename K, typename V, typename C, typename N >
bool spiridonov::detail::Tree< K, V, C, N >::Iterator::operator!=(const this_t& rhs) const
{
  return !(rhs == *this);
}
template < typename K, typename V, typename C, typename N >
bool spiridonov::detail::Tree< K, V, C, N >::Iterator::operator==(const this_t& rhs) const
{
  return iter_ == rhs.iter_;
}

template < typename Key, typename Value, typename Compare, typename Node >
class spiridonov::detail::Tree< Key, Value, Compare, Node >::ConstIterator: std::iterator< std::forward_iterator_tag, std::pair< Key, Value > >
{
public:
  friend class Tree;
  using this_t = ConstIterator;
  using tree_data_t = spiridonov::tree_data_t< Key, Value, Compare, Node >;

  ConstIterator();
  ConstIterator(const this_t&) = default;
  ~ConstIterator() = default;
  this_t& operator=(const this_t&) = default;

  tree_citer_t< Key, Value, Compare, Node >& operator++();
  tree_citer_t< Key, Value, Compare, Node > operator++(int);
  tree_citer_t< Key, Value, Compare, Node >& operator--();
  tree_citer_t< Key, Value, Compare, Node > operator--(int);

  const tree_data_t& operator*() const;
  const tree_data_t* operator->() const;

  bool operator!=(const this_t&) const;
  bool operator==(const this_t&) const;

private:
  using node_t = Tree< Key, Value, Compare, Node >::node_t;
  node_t* node_;
  const Tree< Key, Value, Compare, Node >* tree_;

  ConstIterator(node_t*, const Tree< Key, Value, Compare, Node >*);
  void next();
};
template < typename K, typename V, typename C, typename N >
spiridonov::detail::Tree< K, V, C, N >::ConstIterator::ConstIterator():
  node_(nullptr),
  tree_(nullptr)
{}
template < typename K, typename V, typename C, typename N >
spiridonov::detail::Tree< K, V, C, N >::ConstIterator::ConstIterator(node_t* node, const Tree< K, V, C, N >* tree):
  node_(node),
  tree_(tree)
{}
template < typename K, typename V, typename C, typename N >
typename spiridonov::tree_citer_t< K, V, C, N >& spiridonov::detail::Tree< K, V, C, N >::ConstIterator::operator++()
{
  assert(!tree_->isNil(node_));
  node_ = tree_->getNext(node_);
  return *this;
}
template < typename K, typename V, typename C, typename N >
typename spiridonov::tree_citer_t< K, V, C, N > spiridonov::detail::Tree< K, V, C, N >::ConstIterator::operator++(int)
{
  assert(!tree_->isNil(node_));
  this_t result(*this);
  ++(*this);
  return result;
}
template < typename K, typename V, typename C, typename N >
typename spiridonov::tree_citer_t< K, V, C, N >& spiridonov::detail::Tree< K, V, C, N >::ConstIterator::operator--()
{
  assert(!tree_->isNil(node_));
  node_ = tree_->getPrev(node_);
  return *this;
}
template < typename K, typename V, typename C, typename N >
typename spiridonov::tree_citer_t< K, V, C, N > spiridonov::detail::Tree< K, V, C, N >::ConstIterator::operator--(int)
{
  assert(!tree_->isNil(node_));
  this_t result(*this);
  --(*this);
  return result;
}
template < typename K, typename V, typename C, typename N >
const typename spiridonov::tree_data_t< K, V, C, N >& spiridonov::detail::Tree< K, V, C, N >::ConstIterator::operator*() const
{
  return node_->data_;
}
template < typename K, typename V, typename C, typename N >
const typename spiridonov::tree_data_t< K, V, C, N >* spiridonov::detail::Tree< K, V, C, N >::ConstIterator::operator->() const
{
  return std::addressof(node_->data_);
}
template < typename K, typename V, typename C, typename N >
bool spiridonov::detail::Tree< K, V, C, N >::ConstIterator::operator!=(const this_t& rhs) const
{
  return !(*this == rhs);
}
template < typename K, typename V, typename C, typename N >
bool spiridonov::detail::Tree< K, V, C, N >::ConstIterator::operator==(const this_t& rhs) const
{
  return node_ == rhs.node_;
}

template < typename K, typename V, typename C, typename N >
spiridonov::detail::Tree< K, V, C, N >::Tree():
  nil_(static_cast< node_t* >(operator new(sizeof(node_t)))),
  root_(nil_)
{}

template < typename K, typename V, typename C, typename N >
spiridonov::detail::Tree< K, V, C, N >::Tree(const this_t& other):
  Tree()
{
  if (other.root_ != other.nil_)
  {
    node_t* other_node = other.root_;
    node_t* new_node = new node_t{other_node->data_, nil_, nil_, nil_};

    try
    {
      add(new_node, other_node, other.nil_);
      root_ = new_node;
    }
    catch (...)
    {
      clear(new_node);
      throw;
    }
  }
}

template < typename K, typename V, typename C, typename N >
spiridonov::detail::Tree< K, V, C, N >::Tree(this_t&& other) noexcept:
  nil_(other.nil_),
  root_(other.root_)
{
  other.root_ = nullptr;
  other.nil_ = nullptr;
}

template < typename K, typename V, typename C, typename N >
spiridonov::detail::Tree< K, V, C, N >::~Tree()
{
  clear(root_);
  if (!isNil(root_))
  {
    delete root_;
  }
  if (nil_)
  {
    operator delete(nil_);
  }
}

template < typename K, typename V, typename C, typename N >
spiridonov::detail::Tree< K, V, C, N >& spiridonov::detail::Tree< K, V, C, N >::operator=(const this_t& other)
{
  if (this != std::addressof(other))
  {
    this_t temp(other);
    swap(temp);
  }
  return *this;
}

template < typename K, typename V, typename C, typename N >
spiridonov::detail::Tree< K, V, C, N >& spiridonov::detail::Tree< K, V, C, N >::operator=(this_t&& other) noexcept
{
  if (this != std::addressof(other))
  {
    this_t temp(std::move(other));
    swap(temp);
  }
  return *this;
}

template < typename K, typename V, typename C, typename N >
void spiridonov::detail::Tree< K, V, C, N >::swap(this_t& other) noexcept
{
  std::swap(nil_, other.nil_);
  std::swap(root_, other.root_);
}

template < typename K, typename V, typename C, typename N >
void spiridonov::detail::Tree< K, V, C, N >::push(const K& key, const V& value)
{
  doPush(key, value);
}

template < typename K, typename V, typename C, typename N >
template < typename... Args >
typename spiridonov::detail::Tree< K, V, C, N >::Iterator spiridonov::detail::Tree< K, V, C, N >::emplace(const K& key, Args&&... args)
{
  return ConstIterator(doPush(key, V(std::forward< Args >(args)...)), this);
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::Iterator spiridonov::detail::Tree< K, V, C, N >::get(const K& key)
{
  return doGet(key);
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::Iterator spiridonov::detail::Tree< K, V, C, N >::upperBound(const K& key)
{
  return const_cast< const this_t& >(*this).upperBound(key);
}
template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::Iterator spiridonov::detail::Tree< K, V, C, N >::lowerBound(const K& key)
{
  return const_cast< const this_t& >(*this).lowerBound(key);
}
template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::ConstIterator spiridonov::detail::Tree< K, V, C, N >::upperBound(const K& key) const
{
  ConstIterator iter = cbegin();
  while (iter != cend() && C()(getKey(iter->node_), key))
  {
    iter++;
  }
  return iter;
}
template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::ConstIterator spiridonov::detail::Tree< K, V, C, N >::lowerBound(const K& key) const
{
  ConstIterator iter = cbegin();
  while (iter != cend() && !C()(key, getKey(iter->node_)))
  {
    iter++;
  }
  return iter;
}

template < typename K, typename V, typename C, typename N >
bool spiridonov::detail::Tree< K, V, C, N >::isEmpty() const noexcept
{
  return isNil(root_);
}

template < typename K, typename V, typename C, typename N >
void spiridonov::detail::Tree< K, V, C, N >::clear(node_t* node)
{
  if (!isNil(node))
  {
    clear(node->left_);
    clear(node->right_);
    if (!isNil(node->left_))
    {
      delete node->left_;
    }
    if (!isNil(node->right_))
    {
      delete node->right_;
    }
  }
}

template < typename K, typename V, typename C, typename N >
void spiridonov::detail::Tree< K, V, C, N >::add(node_t* dist, node_t* from, node_t* from_nil)
{
  if (from->left_ != from_nil)
  {
    dist->left_ = new node_t{from->left_->data_, nil_, nil_, dist};
    add(dist->left_, from->left_, from_nil);
  }
  if (from->right_ != from_nil)
  {
    dist->right_ = new node_t{from->right_->data_, nil_, nil_, dist};
    add(dist->right_, from->right_, from_nil);
  }
}

template < typename K, typename V, typename C, typename N >
void spiridonov::detail::Tree< K, V, C, N >::rotateSmallLeft(node_t* node)
{
  if (!isHasParent(node) || isLeft(node))
  {
    return;
  }
  node_t* left = node->left_;

  node->left_ = node->parent_;
  node->parent_ = node->parent_->parent_;
  node->left_->parent_ = node;
  if (!isNil(node->parent_))
  {
    node_t* parent = node->parent_;
    if (parent->left_ == node->left_)
    {
      parent->left_ = node;
    }
    else if (parent->right_ == node->left_)
    {
      parent->right_ = node;
    }
  }
  else
  {
    root_ = node;
  }

  node_t* past_parent = node->left_;
  past_parent->right_ = left;
  if (left && !isNil(left))
  {
    left->parent_ = past_parent;
  }
}

template < typename K, typename V, typename C, typename N >
void spiridonov::detail::Tree< K, V, C, N >::rotateSmallRight(node_t* node)
{
  if (!isHasParent(node) || isLeft(node))
  {
    return;
  }
  node_t* right = node->right_;

  node->right_ = node->parent_;
  node->parent_ = node->parent_->parent_;
  node->right_->parent_ = node;
  if (!isNil(node->parent_))
  {
    node_t* parent = node->parent_;
    if (parent->right_ == node->right_)
    {
      parent->right_ = node;
    }
    else if (parent->left_ == node->right_)
    {
      parent->left_ = node;
    }
  }
  else
  {
    root_ = node;
  }

  node_t* past_parent = node->right_;
  past_parent->left_ = right;
  if (right && !isNil(right))
  {
    right->parent_ = past_parent;
  }
}

template < typename K, typename V, typename C, typename N >
void spiridonov::detail::Tree< K, V, C, N >::rotateBigLeft(node_t* node)
{
  if (!isHasGrandParent(node) || isRight(node) || isLeft(node->parent_))
  {
    return;
  }
  rotateSmallRight(node);
  rotateSmallLeft(node);
}

template < typename K, typename V, typename C, typename N >
void spiridonov::detail::Tree< K, V, C, N >::rotateBigRight(node_t* node)
{
  if (!isHasGrandParent(node) || isLeft(node) || isRight(node->parent_))
  {
    return;
  }
  rotateSmallLeft(node);
  rotateSmallRight(node);
}

template < typename K, typename V, typename C, typename N >
bool spiridonov::detail::Tree< K, V, C, N >::isNil(node_t* node) const
{
  return node == nil_;
}

template < typename K, typename V, typename C, typename N >
bool spiridonov::detail::Tree< K, V, C, N >::isLeftOutside(node_t* node) const
{
  if (isNil(root_))
  {
    return false;
  }
  if (node == root_->left_)
  {
    return true;
  }
  return isLeft(node) && isLeftOutside(node->parent_);
}

template < typename K, typename V, typename C, typename N >
bool spiridonov::detail::Tree< K, V, C, N >::isLeft(node_t* node) const
{
  if (isNil(node) || isNil(node->parent_))
  {
    return false;
  }
  return node->parent_->left_ == node;
}

template < typename K, typename V, typename C, typename N >
bool spiridonov::detail::Tree< K, V, C, N >::isRight(node_t* node) const
{
  if (isNil(node) || isNil(node->parent_))
  {
    return false;
  }
  return node->parent_->right_ == node;
}

template < typename K, typename V, typename C, typename N >
bool spiridonov::detail::Tree< K, V, C, N >::isHasParent(node_t* node) const
{
  if (isNil(node))
  {
    return !isNil(node->parent_);
  }
  return !isNil(node) && !isNil(node->parent_);
}

template < typename K, typename V, typename C, typename N >
bool spiridonov::detail::Tree< K, V, C, N >::isHasGrandParent(node_t* node) const
{
  return isHasParent(node) && isHasParent(node->parent_);
}

template < typename K, typename V, typename C, typename N >
bool spiridonov::detail::Tree< K, V, C, N >::isHasUncle(node_t* node) const
{
  if (!isHasGrandParent(node))
  {
    return false;
  }
  node_t* grand_parent = getGrandParent(node);
  return (isLeft(node) && !isNil(grand_parent->right_)) || (isRight(node) && !isNil(grand_parent->left_));
}

template < typename K, typename V, typename C, typename N >
bool spiridonov::detail::Tree< K, V, C, N >::isHasChild(node_t* node) const
{
  return !isNil(node) && (!isNil(node->left_) || !isNil(node->right_));
}

template < typename K, typename V, typename C, typename N >
const K& spiridonov::detail::Tree< K, V, C, N >::getKey(const node_t* node) const
{
  return node->data_.first;
}

template < typename K, typename V, typename C, typename N >
size_t spiridonov::detail::Tree< K, V, C, N >::getHeight(node_t* node) const
{
  if (!node || isNil(node))
  {
    return 0ul;
  }
  return std::max(getHeight(node->right_), getHeight(node->left_)) + 1ul;
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::node_t* spiridonov::detail::Tree< K, V, C, N >::doSearch(const K& key)
{
  return const_cast< node_t* >(static_cast< const Tree< K, V, C, N >& >(*this).doSearch(key));
}

template < typename K, typename V, typename C, typename N >
const typename spiridonov::detail::Tree< K, V, C, N >::node_t* spiridonov::detail::Tree< K, V, C, N >::doSearch(const K& key) const
{
  if (isNil(root_))
  {
    return nil_;
  }
  node_t* root_node = root_;
  if (getKey(root_) == key)
  {
    return root_node;
  }
  while (!isNil(root_node))
  {
    if (!C()(getKey(root_node), key))
    {
      if (!isNil(root_node->left_) && getKey(root_node->left_) == key)
      {
        return root_node->left_;
      }
      root_node = root_node->left_;
    }
    else
    {
      if (!isNil(root_node->right_) && getKey(root_node->right_) == key)
      {
        return root_node->right_;
      }
      root_node = root_node->right_;
    }
  }
  return nil_;
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::ConstIterator spiridonov::detail::Tree< K, V, C, N >::doGet(const K& key) const
{
  return ConstIterator(static_cast< node_t* >(const_cast< Tree< K, V, C, N >& >(*this).doSearch(key)), this);
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::ConstIterator spiridonov::detail::Tree< K, V, C, N >::getIter(node_t* node) const
{
  return ConstIterator(node, this);
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::node_t* spiridonov::detail::Tree< K, V, C, N >::doPush(const K& key, const V& value)
{
  if (isNil(root_))
  {
    root_ = new node_t{std::make_pair(key, value), nil_, nil_, nil_};
    return root_;
  }
  node_t* root_node = root_;
  while (!isNil(root_node))
  {
    if (getKey(root_node) == key)
    {
      throw std::logic_error("Not uniqual key");
    }
    if (!C()(getKey(root_node), key))
    {
      if (!isNil(root_node->left_))
      {
        root_node = root_node->left_;
      }
      else
      {
        root_node->left_ = new node_t{std::make_pair(key, value), nil_, nil_, root_node};
        root_node = root_node->left_;
        break;
      }
    }
    else
    {
      if (!isNil(root_node->right_))
      {
        root_node = root_node->right_;
      }
      else
      {
        root_node->right_ = new node_t{std::make_pair(key, value), nil_, nil_, root_node};
        root_node = root_node->right_;
        break;
      }
    }
  }
  return root_node;
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::node_t* spiridonov::detail::Tree< K, V, C, N >::getMin(node_t* node) const
{
  if (!node || isNil(node))
  {
    return nil_;
  }
  while (!isNil(node->left_))
  {
    node = node->left_;
  }
  return node;
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::node_t* spiridonov::detail::Tree< K, V, C, N >::getMax(node_t* node) const
{
  if (!node || isNil(node))
  {
    return nil_;
  }
  while (!isNil(node->right_))
  {
    node = node->right_;
  }
  return node;
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::node_t* spiridonov::detail::Tree< K, V, C, N >::getParent(node_t* node) const
{
  if (!node || isNil(node))
  {
    return nil_;
  }
  return node->parent_;
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::node_t* spiridonov::detail::Tree< K, V, C, N >::getGrandParent(node_t* node) const
{
  return getParent(getParent(node));
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::node_t* spiridonov::detail::Tree< K, V, C, N >::getUncle(node_t* node) const
{
  if (isLeft(node))
  {
    return getGrandParent(node)->right_;
  }
  return getGrandParent(node)->left_;
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::node_t* spiridonov::detail::Tree< K, V, C, N >::getNext(node_t* node) const
{
  if (isNil(node))
  {
    node = root_;
    if (isNil(node))
    {
      throw std::underflow_error("Empty");
    }
    while (!isNil(node->left_))
    {
      node = node->left_;
    }
  }
  else if (!isNil(node->right_))
  {
    node = node->right_;
    while (!isNil(node->left_))
    {
      node = node->left_;
    }
  }
  else
  {
    node_t* temp = node->parent_;
    while (!isNil(temp) && node == temp->right_)
    {
      node = temp;
      temp = temp->parent_;
    }
    node = temp;
  }

  return node;
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::node_t* spiridonov::detail::Tree< K, V, C, N >::getPrev(node_t* node) const
{
  if (isNil(node))
  {
    node = root_;
    if (isNil(node))
    {
      throw std::underflow_error("Empty");
    }
    while (!isNil(node->right_))
    {
      node = node->right_;
    }
  }
  else if (!isNil(node->left_))
  {
    node = node->left_;
    while (!isNil(node->right_))
    {
      node = node->right_;
    }
  }
  else
  {
    node_t* temp = node->parent_;
    while (!isNil(temp) && node == temp->left_)
    {
      node = temp;
      temp = temp->parent_;
    }
    node = temp;
  }

  return node;
}

template < typename K, typename V, typename C, typename N >
template < typename F >
F spiridonov::detail::Tree< K, V, C, N >::traverseLnr(F f) const
{
  if (isEmpty())
  {
    return f;
  }
  Stack< node_t* > stack;
  node_t* temp = root_;
  while (!stack.isEmpty() || !isNil(temp))
  {
    if (!isNil(temp))
    {
      stack.push(temp);
      temp = temp->left_;
    }
    else
    {
      temp = stack.getTop();
      stack.drop();
      f(temp->data_);
      temp = temp->right_;
    }
  }
  return f;
}

template < typename K, typename V, typename C, typename N >
template < typename F >
F spiridonov::detail::Tree< K, V, C, N >::traverseRnl(F f) const
{
  if (isEmpty())
  {
    return f;
  }
  Stack< node_t* > stack;
  node_t* temp = root_;
  while (!stack.isEmpty() || !isNil(temp))
  {
    if (!isNil(temp))
    {
      stack.push(temp);
      temp = temp->right_;
    }
    else
    {
      temp = stack.getTop();
      stack.drop();
      f(temp->data_);
      temp = temp->left_;
    }
  }
  return f;
}

template < typename K, typename V, typename C, typename N >
template < typename F >
F spiridonov::detail::Tree< K, V, C, N >::traverseBreadth(F f) const
{
  if (isEmpty())
  {
    return f;
  }
  Queue< node_t* > queue;
  queue.push(root_);
  while (!queue.isEmpty())
  {
    node_t* node = queue.getNext();
    queue.drop();
    f(node->data_);
    if (!isNil(node->left_))
    {
      queue.push(node->left_);
    }
    if (!isNil(node->right_))
    {
      queue.push(node->right_);
    }
  }
  return f;
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::Iterator spiridonov::detail::Tree< K, V, C, N >::begin() noexcept
{
  return cbegin();
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::Iterator spiridonov::detail::Tree< K, V, C, N >::end() noexcept
{
  return cend();
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::ConstIterator spiridonov::detail::Tree< K, V, C, N >::begin() const noexcept
{
  return cbegin();
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::ConstIterator spiridonov::detail::Tree< K, V, C, N >::end() const noexcept
{
  return cend();
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::ConstIterator spiridonov::detail::Tree< K, V, C, N >::cbegin() const noexcept
{
  return ConstIterator(getMin(root_), this);
}

template < typename K, typename V, typename C, typename N >
typename spiridonov::detail::Tree< K, V, C, N >::ConstIterator spiridonov::detail::Tree< K, V, C, N >::cend() const noexcept
{
  return ConstIterator(nil_, this);
}

#endif
