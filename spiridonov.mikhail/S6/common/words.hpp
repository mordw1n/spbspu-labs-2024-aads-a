#ifndef WORDS_HPP_S2
#define WORDS_HPP_S2

#include <string>
#include <iterator>

namespace spiridonov
{
  using word_t = std::string;
  class Words
  {
  public:
    class Iterator;
    using this_t = Words;

    Words() = delete;
    Words(const std::string&);
    Words(const this_t&) = default;
    ~Words() = default;

    Iterator begin() noexcept;
    Iterator end() noexcept;

  private:
    std::string str_;
  };
}

class spiridonov::Words::Iterator: public std::iterator< std::forward_iterator_tag, word_t, std::ptrdiff_t, word_t, word_t >
{
public:
  friend class Words;
  using this_t = Iterator;

  Iterator() = delete;
  Iterator(const this_t&) = default;
  ~Iterator() = default;
  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);

  word_t operator*();
  word_t operator->();

  bool operator==(const this_t&) const;
  bool operator!=(const this_t&) const;

private:
  word_t* str_;
  size_t last_space_ = 0;
  size_t next_space_ = 0;

  Iterator(word_t*, size_t);
  word_t getWord();
  bool isEnd() const noexcept;
};

#endif
