#ifndef COMMANDS_SYSTEM_HPP_S2
#define COMMANDS_SYSTEM_HPP_S2

#include <functional>
#include <stdexcept>

namespace spiridonov
{
  template < typename Func, typename Container >
  struct CommandSystem
  {
    CommandSystem() = default;
    CommandSystem(const Container&);
    ~CommandSystem() = default;
    Func operator()(const std::string&);
    void addCommand(const std::string&, Func);

  private:
    Container commands_;
  };
}

template < typename Func, typename Container >
spiridonov::CommandSystem< Func, Container >::CommandSystem(const Container& c):
  commands_(c)
{}

template < typename Func, typename Container >
Func spiridonov::CommandSystem< Func, Container >::operator()(const std::string& c)
{
  typename Container::Iterator iterator = commands_.get(c);
  if (iterator == commands_.end())
  {
    throw std::out_of_range("Out of range!");
  }
  return iterator->second;
}

template < typename Func, typename Container >
void spiridonov::CommandSystem< Func, Container >::addCommand(const std::string& name, Func func)
{
  commands_.push(name, func);
}

#endif
