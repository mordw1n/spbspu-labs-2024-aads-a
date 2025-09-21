#include "words.hpp"
#include <string>
#include <cassert>

spiridonov::Words::Words(const std::string& str):
  str_(str)
{}

spiridonov::Words::Iterator spiridonov::Words::begin() noexcept
{
  return Iterator(std::addressof(str_), 0);
}

spiridonov::Words::Iterator spiridonov::Words::end() noexcept
{
  return Iterator(std::addressof(str_), str_.size() + 1);
}

spiridonov::Words::Iterator::Iterator(std::string* str, size_t begin):
  str_(str),
  last_space_(begin),
  next_space_(begin)
{
  next_space_ = str_->find_first_of(' ', last_space_ + 1);
  next_space_ = (next_space_ == str_->npos) ? str_->size() : next_space_;
}

spiridonov::Words::Iterator::this_t& spiridonov::Words::Iterator::operator++()
{
  assert(!isEnd());
  last_space_ = next_space_ + 1;
  next_space_ = str_->find_first_of(' ', last_space_ + 1);
  next_space_ = (next_space_ == str_->npos) ? str_->size() : next_space_;
  return *this;
}

spiridonov::Words::Iterator::this_t spiridonov::Words::Iterator::operator++(int)
{
  assert(!isEnd());
  this_t result(*this);
  ++(*this);
  return result;
}

spiridonov::word_t spiridonov::Words::Iterator::operator*()
{
  assert(!isEnd());
  return getWord();
}

spiridonov::word_t spiridonov::Words::Iterator::operator->()
{
  assert(!isEnd());
  return getWord();
}

bool spiridonov::Words::Iterator::operator==(const this_t& rhs) const
{
  return str_ == rhs.str_ && last_space_ == rhs.last_space_ && next_space_ == rhs.next_space_;
}

bool spiridonov::Words::Iterator::operator!=(const this_t& rhs) const
{
  return !(rhs == *this);
}

spiridonov::word_t spiridonov::Words::Iterator::getWord()
{
  return str_->substr(last_space_, next_space_ - last_space_);
}

bool spiridonov::Words::Iterator::isEnd() const noexcept
{
  return last_space_ >= str_->size();
}
