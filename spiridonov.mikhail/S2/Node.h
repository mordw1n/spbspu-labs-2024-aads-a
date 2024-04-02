#ifndef NODE_H
#define NODE_H

namespace spiridonov
{
  template < typename T >

  struct Node
  {
    T data_;
    Node< T >* next_;
  };

}

#endif
