#include "poly.hpp"

#include <iostream>
#include <math.h>

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
template<typename T> Poly<T>::Poly(Poly<T> && ploy)
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



void doTest( const Poly<TYPE> & poly, TYPE param, TYPE expectation ) {
  TYPE result = poly.eval(param)-expectation;
  if( fabs(result) > 0.000001 )
    std::cout << "Error!\n";
  else
    std::cout << "Success!\n";
}

int main() {
  
  //testing interface of the polynomial class

  //constructors
  Poly<TYPE> p1;                                      doTest(p1,10,0);
  Poly<TYPE> p2(2);                                   doTest(p2,10,2);
  std::vector<TYPE> cs{ 0, 1, 0, -2};
  Poly<TYPE> p3(cs);                                  doTest(p3,2,-14);
  Poly<TYPE> p4(std::vector<TYPE>(3,1));              doTest(p4,3,13);
  TYPE arr[] = {1,0,2};
  Poly<TYPE> p5(arr,3);                               doTest(p5,3,19);
  Poly<TYPE> p6{2,0,-1};                              doTest(p6,3,-7);
  
  //copy/move constructor
  Poly<TYPE> p7(p3);                                  doTest(p7,2,-14);
  Poly<TYPE> p8(Poly<TYPE>(std::vector<TYPE>(3,1)));  doTest(p8,3,13);

  //assignments
  p8 = p7;                                            doTest(p8,2,-14);
  p8 = Poly<TYPE>{2,0,-1};                            doTest(p8,3,-7);

  //operations
  Poly<TYPE> p9 = p3 + p4;                            doTest(p9,2,-7);
  Poly<TYPE> p10 = p9 - p3;                           doTest(p10,3,13);
  p10 *= p9;
  TYPE res1 = p10.eval(-4);
  TYPE res2 = p4.eval(-4) * p9.eval(-4);
  if( fabs(res1-res2) < 0.000001 )
    std::cout << "Success!\n";
  else
    std::cout << "Error!\n";

  //evaluators
  doTest(p4.der(),2,5);
  std::pair<TYPE,TYPE> res = p4(2);
  if(fabs(res.first-7)<0.000001)
    std::cout << "Success!\n";
  else
    std::cout << "Error!\n";
  if(fabs(res.second-5)<0.000001)
    std::cout << "Success!\n";
  else
    std::cout << "Error!\n";
}