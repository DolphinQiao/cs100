#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP 1

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <exception>

class Dynarray {
public:
  Dynarray();
  ~Dynarray();
  explicit Dynarray(std::size_t);
  Dynarray(std::size_t, int);
  Dynarray(const int*,const int*);
  Dynarray(const Dynarray &other);
  Dynarray &operator=(const Dynarray&);
  std::size_t size() const;
  bool empty() const;
  int &at(std::size_t i);
  const int &at(std::size_t i) const;

private:
  int *m_storage;
  std::size_t m_length;
};
Dynarray::Dynarray():m_storage(nullptr), m_length(0){};
Dynarray::Dynarray(std::size_t n): m_storage(new int[n]{}), m_length(n) {
  for(std::size_t i = 0; i < m_length; ++i)
  {
    m_storage[i] = 0;
  }
}
Dynarray::Dynarray(std::size_t n, int x): m_storage(new int[n]{}), m_length(n)
{
  for(std::size_t i = 0; i < m_length; ++i)
  {
    m_storage[i] = x;
  }
}
Dynarray::Dynarray(const int *begin,const int *end):m_storage(new int[end - begin]{}), m_length(end - begin)
{
  for(std::size_t i = 0; i < m_length; ++i)
  {
    m_storage[i] = *(begin+i);
  }
}
Dynarray::Dynarray(const Dynarray &other): m_storage(new int[other.m_length]{}), m_length(other.m_length)
{
  for(std::size_t i = 0; i < m_length; ++i)
  {
    m_storage[i] = other.at(i);
  }
}

Dynarray::~Dynarray(){delete[] m_storage;}


std::size_t Dynarray::size() const{
  return m_length;
}
bool Dynarray::empty() const{
  return (m_length==0);
}
int &Dynarray::at(std::size_t i)
{
  if(i >= m_length) throw std::out_of_range{"Dynarray index out of range!"};
  return m_storage[i];
}
const int &Dynarray::at(std::size_t i) const 
{
  if(i >= m_length) throw std::out_of_range{"Dynarray index out of range!"};
  return m_storage[i];
}
Dynarray& Dynarray::operator=(const Dynarray &other) {
  int *new_data = new int[other.size()];
  for (std::size_t i = 0; i < other.size(); ++i)
  {
    try{
      new_data[i] = other.at(i);
    }catch(...)
    {
      delete[] new_data;
      return *this;
    }
  }
  delete[] m_storage;
  m_storage = new_data;
  m_length = other.size();
  return *this;
}
#endif // DYNARRAY_HPP