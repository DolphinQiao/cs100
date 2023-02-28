#ifndef POLY_HPP_
#define POLY_HPP_

#include <stdlib.h>
#include <vector>

template<typename T>
class Poly {
public:

  /* Default constructor */
  Poly();

  /* Constructor for a poly that's a constant number */
  Poly( T constant );

  /* Given a vector of coefficients */
  Poly( const std::vector<T> & coeffs );

  /* Given an rvalue reference of a vector of coefficients */
  Poly( std::vector<T> && coeffs );

  /* Given an array of coefficients with size of the array*/
  Poly( T * coeffs, size_t numberCoeffs );

  /* Given an initializer_list */
  Poly( std::initializer_list<T> coeffs );

  virtual ~Poly();

  /* Copying constructor */
  Poly( const Poly<T> & poly );

  /* Copying constructor with rvalue reference */
  Poly( Poly<T> && poly );

  /* Assignment operator */
  Poly<T>& operator=( const Poly<T> & poly );
  
  /* Assignment operator with rvalue reference */
  Poly<T>& operator=( Poly<T> && poly );

  /*
   * Below are operations of polynomials.
   * They are quite self-explanatory.
   */

  Poly<T> operator+( const Poly<T> & rhs ) const;
  Poly<T> operator-( const Poly<T> & rhs ) const;
  Poly<T> operator*( const Poly<T> & rhs ) const;

  Poly<T> & operator+=( const Poly<T> & rhs );
  Poly<T> & operator-=( const Poly<T> & rhs );
  Poly<T> & operator*=( const Poly<T> & rhs );

  /* 
   * This function evaluates the polynomial at "param",
   * and returns the value of evaluation.
   * For example, evaluating x+3 at param=7 gives 10. 
   */
  T eval( T param ) const;

  /* 
   * This function takes the derivative of the polynomial,
   * and returns a new polynomial of its derivative.
   * For example, calling this function for x^2
   * will return a polynomial 2x.
   */
  Poly<T> der() const;

  /*
  * This function returns a pair of:
  * 1. the value (evaluation) of the polynomial at "param".
  * 2. the value of the first-order derivative of the polynomial at "param".
  * For example, calling this operator for x^2-2x at "param"=4
  * will return (8, 6).
  */
  std::pair<T,T> operator()( T param ) const;

private:
  std::vector<T> _coeffs;
};

typedef double TYPE;

template<typename T> Poly<T>::Poly(){}
template<typename T> Poly<T>::Poly(T constant)
{
  _coeffs.push_back(constant);
}
template<typename T> Poly<T>::Poly(const std::vector<T> & coeffs)
{
  _coeffs = coeffs;
}
template<typename T> Poly<T>::Poly(std::vector<T> && coeffs)
{
  _coeffs = coeffs;
}
template<typename T> Poly<T>::Poly(T *coeffs, size_t numberCoeffs)
{
  for(int i = 0; i < numberCoeffs; ++i)
  {
    _coeffs.push_back(*(coeffs+i));
  }
}
template<typename T> Poly<T>::Poly(std::initializer_list<T> coeffs)
{
  for(std::initializer_list<T>::iterator it = coeffs.begin(); it != coeffs.end(); ++it)
  {
    _coeffs.push_back(*it);
  }
}
template<typename T> Poly<T>::~Poly()
{
  _coeffs.clear();
}
template<typename T> Poly<T>::Poly(const Poly<T> &poly)
{
  _coeffs = poly._coeffs;
}
template<typename T> Poly<T>::Poly(Poly<T> && poly)
{
  _coeffs = poly._coeffs;
}
template<typename T> Poly<T> & Poly<T>::operator=(const Poly<T> & poly)
{
  _coeffs = poly._coeffs;
  return *this;
}
template<typename T> Poly<T> & Poly<T>::operator=( Poly<T> && poly)
{
  _coeffs = poly._coeffs;
  return *this;
}
template<typename T> Poly<T> Poly<T>::operator+(const Poly<T> &rhs)const
{
  std::vector<T> res;
  res.clear();
  if(_coeffs.size() < rhs._coeffs.size())
  {
    for(int i = 0; i < _coeffs.size(); ++i)
    {
      res.push_back(_coeffs[i] + rhs._coeffs[i]);
    }
    for(int i = _coeffs.size(); i < rhs._coeffs.size(); ++i)
    {
      res.push_back(rhs._coeffs[i]);
    }
  }else
  {
    for(int i = 0; i < rhs._coeffs.size(); ++i)
    {
      res.push_back(_coeffs[i] + rhs._coeffs[i]);
    }
    for(int i = rhs._coeffs.size(); i < _coeffs.size(); ++i)
    {
      res.push_back(_coeffs[i]);
    }
  }
  return Poly(res);
}
template<typename T> Poly<T> Poly<T>::operator-(const Poly<T> &rhs)const
{
  std::vector<T> res;
  res.clear();
  if(_coeffs.size() < rhs._coeffs.size())
  {
    for(int i = 0; i < _coeffs.size(); ++i)
    {
      res.push_back(_coeffs[i] - rhs._coeffs[i]);
    }
    for(int i = _coeffs.size(); i < rhs._coeffs.size(); ++i)
    {
      res.push_back(- rhs._coeffs[i]);
    }
  }else
  {
    for(int i = 0; i < rhs._coeffs.size(); ++i)
    {
      res.push_back(_coeffs[i] - rhs._coeffs[i]);
    }
    for(int i = rhs._coeffs.size(); i < _coeffs.size(); ++i)
    {
      res.push_back(_coeffs[i]);
    }
  }
  return Poly(res);
}
template<typename T> Poly<T> Poly<T>::operator*( const Poly<T> & rhs ) const
{
  std::vector<T> res(_coeffs.size() + rhs._coeffs.size()-1,0);
  for(int i = 0; i < _coeffs.size(); ++i)
  {
    for(int j = 0; j < rhs._coeffs.size(); ++j )
    {
      res[i + j] += _coeffs[i] * rhs._coeffs[j];
    }
  }
  return Poly(res);
}
template<typename T> Poly<T> & Poly<T>::operator+=(const Poly<T> & rhs)
{
  *this = *this + rhs;
  return *this;
}
template<typename T> Poly<T> & Poly<T>::operator-=(const Poly<T> & rhs)
{
  *this = *this - rhs;
  return *this;
}
template<typename T> Poly<T> & Poly<T>::operator*=(const Poly<T> & rhs)
{
  *this = rhs * *this;
  return *this;
}
template<typename T> T Poly<T>::eval( T param) const
{
  T ans = 0;T mul = 1;
  for(int i = 0; i < _coeffs.size(); ++i)
  {
    ans += mul * _coeffs[i];
    mul*=param;
  }
  return ans;
}
template<typename T> Poly<T> Poly<T>::der()const{
  std::vector<T> res;
  res.clear();
  for(int i = 1; i < _coeffs.size(); ++i)
  {
    res.push_back(i * _coeffs[i]);
  }
  return Poly(res);
}
template<typename T> std::pair<T, T> Poly<T>::operator()(T param) const
{
  return std::make_pair(this->eval(param), this->der().eval(param));
}


#endif