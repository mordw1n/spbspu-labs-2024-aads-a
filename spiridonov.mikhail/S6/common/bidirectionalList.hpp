#ifndef BIDIRECTIONAL_LIST_HPP_S2
#define BIDIRECTIONAL_LIST_HPP_S2

#include <stdexcept>
#include <cassert>
#include <iterator>

namespace spiridonov
{
  template < typename T >
  class BidirectionalList
  {
  public:
    class Iterator;
    class ConstIterator;

    BidirectionalList();
    BidirectionalList(const BidirectionalList< T >&);
    BidirectionalList(BidirectionalList< T >&&) noexcept;
    BidirectionalList(std::initializer_list< T >);
    ~BidirectionalList();

    BidirectionalList< T >& operator=(const BidirectionalList< T >&);
    BidirectionalList< T >& operator=(BidirectionalList< T >&&) noexcept;

    bool operator==(const BidirectionalList< T >&) const;
    bool operator!=(const BidirectionalList< T >&) const;

    void pushFront(const T&);
    void pushBack(const T&);
    void insert(const T&, Iterator);
    template < typename... Args >
    Iterator emplaceFront(Args&&...);
    template < typename... Args >
    Iterator emplaceBack(Args&&...);
    template < typename... Args >
    Iterator emplace(Iterator, Args&&...);
    void popFront();
    void popBack();
    Iterator erase(Iterator);

    void swap(BidirectionalList< T >&) noexcept;
    bool isEmpty() const noexcept;

    Iterator begin() noexcept;
    Iterator end() noexcept;

    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

  private:
    struct node_t
    {
      T data_;
      node_t* next_;
      node_t* prev_;
    };
    node_t* end_;
    node_t* head_;
    node_t* tail_;

    void clean();
    bool isEnd(node_t*) const;
  };
}

template < typename T >
class spiridonov::BidirectionalList< T >::Iterator: public std::iterator< std::bidirectional_iterator_tag, T >
{
public:
  friend class BidirectionalList< T >;
  using this_t = Iterator;

  Iterator();
  ~Iterator() = default;
  Iterator(const this_t&) = default;
  Iterator(ConstIterator);
  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);
  this_t& operator--();
  this_t operator--(int);

  T& operator*();
  T* operator->();
  const T& operator*() const;
  const T* operator->() const;

  bool operator!=(const this_t&) const;
  bool operator==(const this_t&) const;

private:
  ConstIterator iter_;
};

template < typename T >
spiridonov::BidirectionalList< T >::Iterator::Iterator():
  iter_()
{}

template < typename T >
spiridonov::BidirectionalList< T >::Iterator::Iterator(ConstIterator iter):
  iter_(iter)
{}

template < typename T >
typename spiridonov::BidirectionalList< T >::Iterator& spiridonov::BidirectionalList< T >::Iterator::operator++()
{
  ++iter_;
  return *this;
}
template < typename T >
typename spiridonov::BidirectionalList< T >::Iterator spiridonov::BidirectionalList< T >::Iterator::operator++(int)
{
  return Iterator(iter_++);
}
template < typename T >
typename spiridonov::BidirectionalList< T >::Iterator& spiridonov::BidirectionalList< T >::Iterator::operator--()
{
  --iter_;
  return *this;
}
template < typename T >
typename spiridonov::BidirectionalList< T >::Iterator spiridonov::BidirectionalList< T >::Iterator::operator--(int)
{
  return Iterator(iter_--);
}

template < typename T >
bool spiridonov::BidirectionalList< T >::Iterator::operator==(const this_t& rhs) const
{
  return rhs.iter_ == iter_;
}

template < typename T >
bool spiridonov::BidirectionalList< T >::Iterator::operator!=(const this_t& rhs) const
{
  return !(rhs == *this);
}
template < typename T >
T& spiridonov::BidirectionalList< T >::Iterator::operator*()
{
  return const_cast< T& >(*iter_);
}
template < typename T >
T* spiridonov::BidirectionalList< T >::Iterator::operator->()
{
  return std::addressof(const_cast< T& >(*iter_));
}
template < typename T >
const T& spiridonov::BidirectionalList< T >::Iterator::operator*() const
{
  return *iter_;
}
template < typename T >
const T* spiridonov::BidirectionalList< T >::Iterator::operator->() const
{
  return std::addressof(*iter_);
}

template < typename T >
class spiridonov::BidirectionalList< T >::ConstIterator: public std::iterator< std::bidirectional_iterator_tag, T >
{
public:
  friend class BidirectionalList< T >;
  using this_t = ConstIterator;

  ConstIterator();
  ~ConstIterator() = default;
  ConstIterator(const this_t&) = default;
  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);
  this_t& operator--();
  this_t operator--(int);

  const T& operator*() const;
  const T* operator->() const;

  bool operator!=(const this_t&) const;
  bool operator==(const this_t&) const;

private:
  node_t* node_;
  const BidirectionalList* list_;
  ConstIterator(node_t*, const BidirectionalList< T >*);
};

template < typename T >
spiridonov::BidirectionalList< T >::ConstIterator::ConstIterator():
  node_(nullptr),
  list_(nullptr)
{}

template < typename T >
spiridonov::BidirectionalList< T >::ConstIterator::ConstIterator(node_t* node, const BidirectionalList< T >* list):
  node_(node),
  list_(list)
{}

template < typename T >
typename spiridonov::BidirectionalList< T >::ConstIterator& spiridonov::BidirectionalList< T >::ConstIterator::operator++()
{
  assert(node_ && !list_->isEnd(node_));
  node_ = node_->next_;
  return *this;
}
template < typename T >
typename spiridonov::BidirectionalList< T >::ConstIterator spiridonov::BidirectionalList< T >::ConstIterator::operator++(int)
{
  this_t result(*this);
  ++(*this);
  return result;
}
template < typename T >
typename spiridonov::BidirectionalList< T >::ConstIterator& spiridonov::BidirectionalList< T >::ConstIterator::operator--()
{
  assert(node_ != nullptr);
  node_ = node_->prev_;
  return *this;
}
template < typename T >
typename spiridonov::BidirectionalList< T >::ConstIterator spiridonov::BidirectionalList< T >::ConstIterator::operator--(int)
{
  this_t result(*this);
  --(*this);
  return result;
}

template < typename T >
bool spiridonov::BidirectionalList< T >::ConstIterator::operator==(const this_t& rhs) const
{
  return node_ == rhs.node_ && list_ == rhs.list_;
}

template < typename T >
bool spiridonov::BidirectionalList< T >::ConstIterator::operator!=(const this_t& rhs) const
{
  return !(rhs == *this);
}
template < typename T >
const T& spiridonov::BidirectionalList< T >::ConstIterator::operator*() const
{
  assert(node_ != nullptr);
  return node_->data_;
}
template < typename T >
const T* spiridonov::BidirectionalList< T >::ConstIterator::operator->() const
{
  assert(node_ != nullptr);
  return std::addressof(node_->data_);
}

template < typename T >
spiridonov::BidirectionalList< T >::BidirectionalList():
  end_(static_cast< node_t* >(operator new(sizeof(node_t)))),
  head_(end_),
  tail_(end_)
{
  end_->prev_ = nullptr;
  end_->next_ = nullptr;
}

template < typename T >
spiridonov::BidirectionalList< T >::BidirectionalList(const BidirectionalList< T >& other):
  BidirectionalList()
{
  if (!other.isEmpty())
  {
    try
    {
      node_t* other_node = other.head_->next_;

      head_ = new node_t{other.head_->data_, nullptr, nullptr};
      node_t* this_node = head_;

      while (other_node && other_node != other.end_)
      {
        this_node->next_ = new node_t{other_node->data_, nullptr, this_node};
        this_node = this_node->next_;
        other_node = other_node->next_;
      }
      tail_ = this_node;
      tail_->next_ = end_;
      end_->prev_ = tail_;
    }
    catch (...)
    {
      clean();
      throw;
    }
  }
}

template < typename T >
spiridonov::BidirectionalList< T >::BidirectionalList(BidirectionalList< T >&& other) noexcept:
  end_(other.end_),
  head_(other.head_),
  tail_(other.tail_)
{
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.end_ = nullptr;
}

template < typename T >
spiridonov::BidirectionalList< T >::BidirectionalList(std::initializer_list< T > il):
  BidirectionalList()
{
  for (auto&& i: il)
  {
    pushBack(i);
  }
}

template < typename T >
spiridonov::BidirectionalList< T >::~BidirectionalList()
{
  clean();
  operator delete(end_);
}

template < typename T >
spiridonov::BidirectionalList< T >& spiridonov::BidirectionalList< T >::operator=(const BidirectionalList< T >& other)
{
  if (this != std::addressof(other))
  {
    BidirectionalList< T > temp(other);
    swap(temp);
  }
  return *this;
}
template < typename T >
spiridonov::BidirectionalList< T >& spiridonov::BidirectionalList< T >::operator=(BidirectionalList< T >&& other) noexcept
{
  if (this != std::addressof(other))
  {
    BidirectionalList< T > temp(std::move(other));
    swap(temp);
  }
  return *this;
}

template < typename T >
void spiridonov::BidirectionalList< T >::swap(BidirectionalList< T >& other) noexcept
{
  std::swap(end_, other.end_);
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
}

template < typename T >
bool spiridonov::BidirectionalList< T >::isEmpty() const noexcept
{
  return !head_ || isEnd(head_);
}

template < typename T >
void spiridonov::BidirectionalList< T >::pushFront(const T& value)
{
  node_t* new_node = new node_t{value, head_, nullptr};
  if (!head_ || isEnd(head_))
  {
    tail_ = new_node;
    tail_->next_ = end_;
    end_->prev_ = tail_;
  }
  else
  {
    head_->prev_ = new_node;
  }
  head_ = new_node;
}

template < typename T >
void spiridonov::BidirectionalList< T >::pushBack(const T& value)
{
  node_t* new_node = new node_t{value, end_, nullptr};
  end_->prev_ = new_node;
  if (!head_ || isEnd(head_))
  {
    head_ = new_node;
    tail_ = new_node;
  }
  else
  {
    new_node->prev_ = tail_;
    tail_->next_ = new_node;
    tail_ = new_node;
  }
}

template < typename T >
void spiridonov::BidirectionalList< T >::insert(const T& value, Iterator iter)
{
  if (iter == begin())
  {
    pushFront(value);
  }
  else if (iter == end())
  {
    pushBack(value);
  }
  else
  {
    node_t* this_node = iter.iter_.node_;
    node_t* new_node = new node_t{value, this_node, this_node->prev_};
    if (this_node->prev_)
    {
      this_node->prev_->next_ = new_node;
    }
    this_node->prev_ = new_node;
    iter.iter_.node_ = new_node;
  }
}

template < typename T >
template < typename... Args >
typename spiridonov::BidirectionalList< T >::Iterator spiridonov::BidirectionalList< T >::emplaceFront(Args&&... args)
{
  pushFront(T(std::forward< Args >(args)...));
  return begin();
}

template < typename T >
template < typename... Args >
typename spiridonov::BidirectionalList< T >::Iterator spiridonov::BidirectionalList< T >::emplaceBack(Args&&... args)
{
  pushBack(T(std::forward< Args >(args)...));
  return end();
}

template < typename T >
template < typename... Args >
typename spiridonov::BidirectionalList< T >::Iterator spiridonov::BidirectionalList< T >::emplace(Iterator iter, Args&&... args)
{
  if (iter == begin())
  {
    return emplaceFront(std::forward< Args >(args)...);
  }
  else if (iter == end())
  {
    return emplaceBack(std::forward< Args >(args)...);
  }
  insert(T(std::forward< Args >(args)...), iter);
}

template < typename T >
void spiridonov::BidirectionalList< T >::popFront()
{
  if (isEmpty())
  {
    throw std::logic_error("Empty!");
  }
  node_t* temp_node = head_->next_;
  if (!temp_node || isEnd(temp_node))
  {
    clean();
  }
  else
  {
    delete head_;
    head_ = temp_node;
    head_->prev_ = nullptr;
  }
}

template < typename T >
void spiridonov::BidirectionalList< T >::popBack()
{
  if (isEmpty())
  {
    throw std::logic_error("Empty!");
  }
  node_t* temp_node = tail_->prev_;
  if (!temp_node || isEnd(temp_node))
  {
    clean();
  }
  else
  {
    delete tail_;
    tail_ = temp_node;
    tail_->next_ = end_;
    end_->prev_ = tail_;
  }
}

template < typename T >
typename spiridonov::BidirectionalList< T >::Iterator spiridonov::BidirectionalList< T >::erase(Iterator iter)
{
  Iterator temp_iter = iter;
  if (iter == end())
  {
    throw std::logic_error("end!");
  }
  if (iter == begin())
  {
    temp_iter++;
    popFront();
  }
  else
  {
    temp_iter++;
    node_t* this_node = iter.iter_.node_;
    this_node->prev_->next_ = this_node->next_;
    if (this_node->next_)
    {
      this_node->next_->prev_ = this_node->prev_;
    }
    delete this_node;
  }
  return temp_iter;
}

template < typename T >
bool spiridonov::BidirectionalList< T >::operator==(const BidirectionalList< T >& other) const
{
  Iterator first = begin();
  Iterator second = other.begin();

  bool is_equal = true;

  while (first != end() && (is_equal = *(first++) == *(second++)))
    ;

  return is_equal;
}

template < typename T >
bool spiridonov::BidirectionalList< T >::operator!=(const BidirectionalList< T >& other) const
{
  return !(*this == other);
}

template < typename T >
void spiridonov::BidirectionalList< T >::clean()
{
  while (head_ && !isEnd(head_))
  {
    node_t* next = head_->next_;
    delete head_;
    head_ = next;
  }
  head_ = end_;
  tail_ = end_;
  end_->prev_ = nullptr;
}

template < typename T >
bool spiridonov::BidirectionalList< T >::isEnd(node_t* node) const
{
  return node == end_;
}

template < typename T >
typename spiridonov::BidirectionalList< T >::Iterator spiridonov::BidirectionalList< T >::begin() noexcept
{
  return cbegin();
}

template < typename T >
typename spiridonov::BidirectionalList< T >::Iterator spiridonov::BidirectionalList< T >::end() noexcept
{
  return cend();
}

template < typename T >
typename spiridonov::BidirectionalList< T >::ConstIterator spiridonov::BidirectionalList< T >::begin() const noexcept
{
  return cbegin();
}

template < typename T >
typename spiridonov::BidirectionalList< T >::ConstIterator spiridonov::BidirectionalList< T >::end() const noexcept
{
  return cend();
}

template < typename T >
typename spiridonov::BidirectionalList< T >::ConstIterator spiridonov::BidirectionalList< T >::cbegin() const noexcept
{
  return ConstIterator(head_, this);
}

template < typename T >
typename spiridonov::BidirectionalList< T >::ConstIterator spiridonov::BidirectionalList< T >::cend() const noexcept
{
  return ConstIterator(end_, this);
}

#endif