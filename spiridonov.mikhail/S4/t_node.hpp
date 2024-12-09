#ifndef TREENODE_H
#define TREENODE_H

#include <utility>

namespace spiridonov
{
  namespace detail
  {
    template < class Key, class Value >

    struct TNode
    {
      using KV_node = TNode< Key, Value >;

      std::pair< Key, Value > data_;
      KV_node *parent_;
      KV_node *left_;
      KV_node *right_;
      int height_;

      TNode(Key key_, Value value_, KV_node *parent = nullptr):
        data_(key_, value_),
        parent_(parent),
        left_(nullptr),
        right_(nullptr),
        height_(0)
      {}

      ~TNode()
      {}

    };
  }
}

#endif
