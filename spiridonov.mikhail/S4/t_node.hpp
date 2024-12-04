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
      using KV_tnode_t = TNode< Key, Value >;

      std::pair< Key, Value > data_;
      KV_tnode_t *parent_;
      KV_tnode_t *left_;
      KV_tnode_t *right_;
      int height_;

      TNode(Key key_, Value value_, KV_tnode_t *parent = nullptr):
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
