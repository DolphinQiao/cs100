#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP 1

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <exception>

class Dynarray {
public:
  using size_type = std::size_t;
  using value_type = int;
  using pointer = int *;
  using reference = int &;
  using const_pointer = const int *;
  using const_reference = const int &;
  static const Dynarray::size_type npos = static_cast<std::size_t>(-1);
  Dynarray();
  ~Dynarray();
  explicit Dynarray(Dynarray::size_type);
  Dynarray(Dynarray::size_type, Dynarray::value_type);
  Dynarray(Dynarray::const_pointer,Dynarray::const_pointer);
  Dynarray(const Dynarray &);
  Dynarray(Dynarray &&) noexcept;
  Dynarray &operator=(const Dynarray&);
  Dynarray &operator=(Dynarray &&) noexcept;
  std::size_t size() const;
  bool empty() const;
  Dynarray::reference at(Dynarray::size_type);
  Dynarray::const_reference at(Dynarray::size_type) const;
  Dynarray::size_type find(Dynarray::value_type, Dynarray::size_type) const;

private:
  Dynarray::pointer m_storage;
  Dynarray::size_type m_length;
};
Dynarray::Dynarray():m_storage(nullptr), m_length(0u){};
Dynarray::Dynarray(Dynarray::size_type n): m_storage(new Dynarray::value_type[n]{}), m_length(n) {
  for(Dynarray::size_type i = 0; i < m_length; ++i)
  {
    m_storage[i] = 0;
  }
}
Dynarray::Dynarray(Dynarray::size_type n, Dynarray::value_type x): m_storage(new Dynarray::value_type[n]{}), m_length(n)
{
  for(Dynarray::size_type i = 0; i < m_length; ++i)
  {
    m_storage[i] = x;
  }
}
Dynarray::Dynarray(Dynarray::const_pointer begin, Dynarray::const_pointer end):m_storage(new Dynarray::value_type[end - begin]{}), m_length(end - begin)
{
  for(Dynarray::size_type i = 0; i < m_length; ++i)
  {
    m_storage[i] = *(begin+i);
  }
}
Dynarray::Dynarray(const Dynarray &other): m_storage(new Dynarray::value_type[other.m_length]{}), m_length(other.m_length)
{
  for(Dynarray::size_type i = 0; i < m_length; ++i)
  {
    m_storage[i] = other.at(i);
  }
}

Dynarray::Dynarray(Dynarray &&other) noexcept : m_storage(std::move(other.m_storage)), m_length(std::move(other.m_length)){
  other.m_length = static_cast<Dynarray::size_type>(0);
  other.m_storage = nullptr;
}

Dynarray::~Dynarray(){delete[] m_storage;}

Dynarray::size_type Dynarray::size() const{
  return m_length;
}
bool Dynarray::empty() const{
  return (m_length==0);
}
Dynarray::value_type &Dynarray::at(Dynarray::size_type i)
{
  if(i >= m_length) throw std::out_of_range{"Dynarray index out of range!"};
  return m_storage[i];
}
Dynarray::const_reference Dynarray::at(Dynarray::size_type i) const 
{
  if(i >= m_length) throw std::out_of_range{"Dynarray index out of range!"};
  return m_storage[i];
}
Dynarray& Dynarray::operator=(const Dynarray &other) {
  Dynarray::pointer new_data = new Dynarray::value_type[other.size()];
  for (Dynarray::size_type i = 0; i < other.size(); ++i)
  {
      new_data[i] = other.at(i);
  }
  delete[] m_storage;
  m_storage = new_data;
  m_length = other.size();
  return *this;
}

Dynarray& Dynarray::operator=(Dynarray &&other) noexcept{
  if(this != &other)
  {
    delete[] m_storage;
    m_length = std::move(other.m_length);
    m_storage = std::move(other.m_storage);
    other.m_length = static_cast<Dynarray::size_type>(0);
    other.m_storage = nullptr;
  }
  return *this;
}

Dynarray::size_type Dynarray::find(Dynarray::value_type val, Dynarray::size_type pos = 0) const
{
  for(Dynarray::size_type i = pos; i < size(); ++i)
  {
    if(m_storage[i] == val) return i;
  }
  return Dynarray::npos;
}

#endif // DYNARRAY_HPP