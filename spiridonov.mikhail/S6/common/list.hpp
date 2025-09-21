#ifndef LIST_HPP_S1
#define LIST_HPP_S1

#include <stdexcept>

namespace spiridonov
{
  namespace detail
  {
    template < typename T >
    class List
    {
    public:
      List();
      List(const List< T >&);
      List(List< T >&&) noexcept;
      ~List();

      List< T >& operator=(const List< T >&);
      List< T >& operator=(List< T >&&) noexcept;

      void swap(List< T >&) noexcept;
      void clear();
      bool isEmpty() const;
      void pushFront(const T&);
      void pushBack(const T&);
      void popFront();
      const T& getFront() const;
      const T& getBack() const;

    protected:
      struct node_t
      {
        T data_;
        node_t* next_;
      };
      node_t* head_;
      node_t* tail_;
    };
  }
}

template < typename T >
spiridonov::detail::List< T >::List():
  head_(nullptr),
  tail_(nullptr)
{}

template < typename T >
spiridonov::detail::List< T >::List(const List< T >& other):
  head_(nullptr),
  tail_(nullptr)
{
  if (!other.isEmpty())
  {
    try
    {
      node_t* other_node = other.head_->next_;

      head_ = new node_t{other.head_->data_, nullptr};
      node_t* this_node = head_;

      while (other_node)
      {
        this_node->next_ = new node_t{other_node->data_, nullptr};
        this_node = this_node->next_;
        other_node = other_node->next_;
      }
      tail_ = this_node;
    }
    catch (...)
    {
      clear();
      throw;
    }
  }
}

template < typename T >
spiridonov::detail::List< T >::List(List< T >&& other) noexcept:
  head_(other.head_),
  tail_(other.tail_)
{
  other.head_ = nullptr;
  other.tail_ = nullptr;
}

template < typename T >
spiridonov::detail::List< T >::~List()
{
  clear();
}

template < typename T >
spiridonov::detail::List< T >& spiridonov::detail::List< T >::operator=(const List< T >& other)
{
  if (this != std::addressof(other))
  {
    List< T > temp(other);
    swap(temp);
  }
  return *this;
}
template < typename T >
spiridonov::detail::List< T >& spiridonov::detail::List< T >::operator=(List< T >&& other) noexcept
{
  if (this != std::addressof(other))
  {
    swap(other);
  }
  return *this;
}

template < typename T >
void spiridonov::detail::List< T >::swap(List< T >& other) noexcept
{
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
}

template < typename T >
void spiridonov::detail::List< T >::clear()
{
  while (head_)
  {
    node_t* next = head_->next_;
    delete head_;
    head_ = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

template < typename T >
bool spiridonov::detail::List< T >::isEmpty() const
{
  return !head_;
}

template < typename T >
void spiridonov::detail::List< T >::pushFront(const T& value)
{
  node_t* new_node = new node_t{value, head_};
  if (!head_)
  {
    tail_ = new_node;
  }
  head_ = new_node;
}

template < typename T >
void spiridonov::detail::List< T >::pushBack(const T& value)
{
  node_t* new_node = new node_t{value, nullptr};
  if (head_)
  {
    tail_->next_ = new_node;
    tail_ = new_node;
  }
  else
  {
    head_ = new_node;
    tail_ = head_;
  }
}

template < typename T >
void spiridonov::detail::List< T >::popFront()
{
  if (isEmpty())
  {
    throw std::logic_error("Empty!");
  }
  node_t* temp_node = head_->next_;
  if (head_ == tail_)
  {
    tail_ = nullptr;
  }
  delete head_;
  head_ = temp_node;
}

template < typename T >
const T& spiridonov::detail::List< T >::getFront() const
{
  if (isEmpty())
  {
    throw std::logic_error("Empty!");
  }
  return head_->data_;
}

template < typename T >
const T& spiridonov::detail::List< T >::getBack() const
{
  if (isEmpty())
  {
    throw std::logic_error("Empty!");
  }
  return tail_->data_;
}

#endif
