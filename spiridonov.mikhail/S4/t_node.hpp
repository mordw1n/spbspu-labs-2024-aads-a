#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <utility>

namespace spiridonov
{
  namespace detail
  {
    template<class Key, class Value>
    struct TNode
    {
      std::pair<Key, Value> data_;
      TNode* left_;
      TNode* right_;
      TNode* parent_;
      int height_;

      TNode():
        data_(Key(), Value()),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr),
        height_(0)
      {}

      TNode(const Key& key, const Value& value):
        data_(std::make_pair(key, value)),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr),
        height_(1)
      {}
    };
  }
}

#endif
