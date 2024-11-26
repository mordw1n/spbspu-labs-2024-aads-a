#ifndef TNODE_H
#define TNODE_H

namespace spiridonov
{
  template < class Key, class Value >

  struct TNode
  {
  private:
    using tnode_t = TNode< Key, Value >;

    std::pair< Key, Value > data_;
    TNode< Key, Value > * parent_;
    TNode< Key, Value > * left_;
    TNode< Key, Value > * right_;

    TNode(Key key_, Value value_, TNode< Key, Value >* root_ = nullptr):
      data_(key_, value_),
      parent_(root_),
      left_(nullptr),
      right_(nullptr)
    {}

    void insert(spiridonov::TNode < Key, Value >* node_, Key key_, Value value_)
    {
      if (key_ < node_->data_.first)
      {
        if (node_->left_ == nullptr)
        {
          node_->left_ = new TNode< Key, Value >(key_, value_, node_);
        }
        else
        {
          insert(node_->left_, key_, value_);
        }
      }

      else if (key_ >= node_->data_.first)
      {
        if (node_->right_ == nullptr)
        {
          node_->right_ = new TNode< Key, Value >(key_, value_, node_);
        }
        else
        {
          insert(node_->right_, key_, value_);
        }
      }

    }
    void insert(Key key_, Value value_)
    {
      insert(this, key_, value_);
    }

  };
}

#endif
