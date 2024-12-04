#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>
#include "t_node.hpp"

namespace spiridonov
{
  template< class Key, class Value, class Compare = std::less< Key > >

  class BSTree
  {
    using tnode_t TNode< Key, Value >;
  };
}

#endif
