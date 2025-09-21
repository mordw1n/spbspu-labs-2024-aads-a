#ifndef DICTIONARY_HPP_S2
#define DICTIONARY_HPP_S2

#include <stdexcept>
#include "../common/forwardList.hpp"
#include "../common/AVLTree.hpp"

namespace spiridonov
{
  template < typename Key, typename Value, typename Compare >
  class Dictionary
  {
  public:
    using data_type = std::pair< Key, Value >;
    using Iterator = typename spiridonov::AVLTree< Key, Value, Compare >::Iterator;
    using ConstIterator = typename spiridonov::AVLTree< Key, Value, Compare >::ConstIterator;

    Dictionary() = default;
    Dictionary(std::initializer_list< data_type > il);
    ~Dictionary() = default;

    void push(const Key&, const Value&);
    Iterator get(const Key&);
    ConstIterator get(const Key&) const;
    void drop(const Key&);
    bool isEmpty() const noexcept;

    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;

  private:
    AVLTree< Key, Value, Compare > data_tree_;
  };
  template < typename Key, typename Value, typename Compare >
  using dict_iter_t = typename AVLTree< Key, Value, Compare >::Iterator;
  template < typename Key, typename Value, typename Compare >
  using dict_citer_t = typename AVLTree< Key, Value, Compare >::ConstIterator;
}

template < typename Key, typename Value, typename Compare >
spiridonov::Dictionary< Key, Value, Compare >::Dictionary(std::initializer_list< data_type > il):
  data_tree_()
{
  for (auto&& item: il)
  {
    push(item.first, item.second);
  }
}

template < typename Key, typename Value, typename Compare >
typename spiridonov::dict_iter_t< Key, Value, Compare > spiridonov::Dictionary< Key, Value, Compare >::begin() noexcept
{
  return data_tree_.begin();
}

template < typename Key, typename Value, typename Compare >
typename spiridonov::dict_iter_t< Key, Value, Compare > spiridonov::Dictionary< Key, Value, Compare >::end() noexcept
{
  return data_tree_.end();
}

template < typename Key, typename Value, typename Compare >
typename spiridonov::dict_citer_t< Key, Value, Compare > spiridonov::Dictionary< Key, Value, Compare >::begin() const noexcept
{
  return data_tree_.begin();
}

template < typename Key, typename Value, typename Compare >
typename spiridonov::dict_citer_t< Key, Value, Compare > spiridonov::Dictionary< Key, Value, Compare >::end() const noexcept
{
  return data_tree_.end();
}

template < typename Key, typename Value, typename Compare >
void spiridonov::Dictionary< Key, Value, Compare >::push(const Key& k, const Value& v)
{
  data_tree_.push(k, v);
}

template < typename Key, typename Value, typename Compare >
typename spiridonov::dict_iter_t< Key, Value, Compare > spiridonov::Dictionary< Key, Value, Compare >::get(const Key& k)
{
  return data_tree_.get(k);
}

template < typename Key, typename Value, typename Compare >
typename spiridonov::dict_citer_t< Key, Value, Compare > spiridonov::Dictionary< Key, Value, Compare >::get(const Key& k) const
{
  return data_tree_.get(k);
}

template < typename Key, typename Value, typename Compare >
void spiridonov::Dictionary< Key, Value, Compare >::drop(const Key& k)
{
  return data_tree_.pop(k);
}

template < typename Key, typename Value, typename Compare >
bool spiridonov::Dictionary< Key, Value, Compare >::isEmpty() const noexcept
{
  return data_tree_.isEmpty();
}

#endif
