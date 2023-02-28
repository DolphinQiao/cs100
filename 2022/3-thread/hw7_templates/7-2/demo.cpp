#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

template<typename T> class Matrix{
public:
    Matrix();
    Matrix(unsigned int rows, unsigned int cols, const T& value = T());

    T& operator()(unsigned int r, unsigned int c);
    
    void Print();

    void GaussJordan();

private:
    std::vector<std::vector<T> > m_mat;
};
#endif

#ifndef RATIONAL_HPP
#define RATIONAL_HPP

int gcd(int,int);
class Rational 
{
public:
    // Constructors
    Rational();
    Rational(int value);
    Rational(int p, unsigned int q);

    // Assignment operator
    Rational& operator=(const Rational& that);

    // Arithmetic operators
    Rational  operator+(Rational that) const;
    Rational& operator+=(Rational that);
    Rational  operator-(Rational that) const;
    Rational& operator-=(Rational that);
    Rational  operator*(Rational that) const;
    Rational& operator*=(Rational that);
    Rational  operator/(Rational that) const;
    Rational& operator/=(Rational that);

    // Comparison operators: equal and less than
    bool operator==(Rational that) const;
    bool operator<(Rational that) const;

    // Output
    friend std::ostream& operator<<(std::ostream& os, const Rational& number);

private:
    int m_numerator;
    unsigned int m_denominator;
}; 
#endif
int gcd(int a, int b)
{
  if(a<0) a=-a;
  if (a > b)
    std::swap(a, b);
  if (a == 0)
    return b;
  return gcd(a, b % a);
}

Rational::Rational()
{
  m_denominator = 1;
  m_numerator = 0;
}
Rational::Rational(int value)
{
  m_denominator = 1;
  m_numerator = value;
}
Rational::Rational(int p, unsigned int q)
{
  if(q==0)
  {
    std::cout<<"ERROR: initializing with a denominator of 0!";
    p = 0; q = 1;
    return;
  }
  int g = gcd(p, q);
  m_denominator = q / g;
  m_numerator = p / g;
}
Rational &Rational::operator=(const Rational &that)
{
  m_numerator = that.m_denominator;
  m_denominator = that.m_denominator;
  return *this;
}
Rational Rational::operator+(Rational that) const
{
  int p1, q1, p2, q2;
  p1 = m_numerator;
  p2 = that.m_numerator;
  q1 = m_denominator;
  q2 = that.m_denominator;
  int g = gcd(q1, q2);
  int lcm = q1 * q2 / g;
  p1 *= lcm / q1;
  p2 *= lcm / q2;
  g = gcd(p1 + p2, lcm);
  return Rational((p1 + p2) / g, lcm / g);
}

Rational& Rational::operator+=(Rational that)
{
  int p1, q1, p2, q2;
  p1 = m_numerator;
  p2 = that.m_numerator;
  q1 = m_denominator;
  q2 = that.m_denominator;
  int g = gcd(q1, q2);
  int lcm = q1 * q2 / g;
  p1 *= lcm / q1;
  p2 *= lcm / q2;
  g = gcd(p1 + p2, lcm);
  m_numerator = (p1 + p2) / g;
  m_denominator = lcm / g;
  return *this;
}

Rational Rational::operator-(Rational that)const 
{
  return Rational(m_numerator, m_denominator) + Rational( - that.m_numerator, that.m_denominator);
}

Rational& Rational::operator-=(Rational that)
{
  int p1, q1, p2, q2;
  p1 = m_numerator;
  p2 = - that.m_numerator;
  q1 = m_denominator;
  q2 = that.m_denominator;
  int g = gcd(q1, q2);
  int lcm = q1 * q2 / g;
  p1 *= lcm / q1;
  p2 *= lcm / q2;
  g = gcd(p1 + p2, lcm);
  m_numerator = (p1 + p2) / g;
  m_denominator = lcm / g;
  return *this;
}

Rational Rational::operator*(Rational that)const
{
  int p1, q1, p2, q2;
  p1 = m_numerator;
  p2 = that.m_numerator;
  q1 = m_denominator;
  q2 = that.m_denominator;
  int g=gcd(p1 * p2, q1 * q2);
  return Rational(p1 * p2 / g, q1 * q2 / g);
}

Rational& Rational::operator*=(Rational that)
{
  int p1, q1, p2, q2;
  p1 = m_numerator;
  p2 = that.m_numerator;
  q1 = m_denominator;
  q2 = that.m_denominator;
  int g=gcd(p1 * p2, q1 * q2);
  m_numerator = p1 * p2 / g;
  m_denominator = q1 * q2 / g;
  return *this;
}

Rational Rational::operator/(Rational that)const{
  if(that.m_numerator == 0) 
  {
    std::cout<<"ERROR: dividing by 0!";
  }
  if(that.m_numerator < 0)
    return Rational(m_numerator, m_denominator) * Rational(- that.m_denominator, - that.m_numerator);  
  return Rational(m_numerator, m_denominator) * Rational(that.m_denominator, that.m_numerator);
}
Rational& Rational::operator/=(Rational that){
  if(that.m_numerator == 0) std::cout<<"ERROR: dividing by 0!";
  int p1, q1, p2, q2;
  p1 = m_numerator;
  q2 = that.m_numerator;
  q1 = m_denominator;
  p2 = that.m_denominator;
  int g=gcd(p1 * p2, q1 * q2);
  m_numerator = p1 * p2 / g;
  m_denominator = q1 * q2 / g;
  return *this;
}

bool Rational::operator==(Rational that) const{
  if(m_denominator == that.m_denominator && m_numerator == that.m_numerator)
  {
    return true;
  }
  return false;
}

bool Rational::operator<(Rational that) const{
  int p1, q1, p2, q2;
  p1 = m_numerator;
  p2 = that.m_numerator;
  q1 = m_denominator;
  q2 = that.m_denominator;
  int g=gcd(q1, q2);int lcm=q1 * q2 / g;
  if(lcm / q1 * p1 < lcm / q2 * p2) return true;
  return false;
}

std::ostream& operator<<(std::ostream& os, const Rational& number){
  if(number.m_numerator == 0) return os<<"0";
  return os << number.m_numerator << "/" << number.m_denominator;
}


template <typename T> Matrix<T>::Matrix(){}

template <typename T> Matrix<T>::Matrix(unsigned int rows, unsigned int cols, const T& value)
{
  //std::cout<<rows<<"   "<<cols<<std::endl;
  std::vector<T> tmp;
  for(int i=1;i<=rows;++i)
  {
    tmp.clear();
    for(int j=1;j<=cols;++j)
    {
      tmp.push_back(value);
    }
    m_mat.push_back(tmp);
  }
  // for(int i=1;i<=rows;++i)
  // {
  //   for(int j=1;j<=cols;++j)
  //   {
  //     std::cout<<m_mat[i-1][j-1];
  //   }
  //   std::cout<<std::endl;
  // }
}

template <typename T> T& Matrix<T>::operator()(unsigned int r, unsigned int c)
{
  return m_mat[r][c];
}

template <typename T> void Matrix<T>::Print()
{
  for (int i=0;i<m_mat.size();++i)
  {
    for(int j=0;j<m_mat[0].size();++j)
    {
      std::cout<<m_mat[i][j]<<" ";
    }
    std::cout<<std::endl;
  }
}

template <typename T> void Matrix<T>::GaussJordan()
{
  int h = 0; int k = 0;
  while(h < m_mat.size() && k < m_mat[0].size())
  {
    //std::cout<<"AAA\n";
    int i_max = h;
    int i_min = h;
    for(int i=h+1;i<m_mat.size();++i)
    {
      if(m_mat[i_max][k] < m_mat[i][k]) i_max = i;
      if(m_mat[i][k] < m_mat[i_min][k]) i_min = i;
    }
    if(m_mat[i_max][k] == 0)
    {
      i_max = i_min;
    }
    if(m_mat[i_max][k] == 0)
    {
      k++;
    }else{
      std::swap(m_mat[h],m_mat[i_max]);
      for(int i=h+1;i<m_mat.size();++i)
      {
        T f = m_mat[i][k] / m_mat[h][k];
        m_mat[i][k] = 0;
        for(int j=k+1;j<m_mat[0].size();++j)
        {
          m_mat[i][j] = m_mat[i][j] - m_mat[h][j] * f;
        }
      }
      h++; k++;
    }
  }
}


using namespace std;

void TestDouble()
{
    Matrix<double> matrix(3, 4);
    matrix(0, 0) = 0;    matrix(0, 1) = 0.4;  matrix(0, 2) = 0.2;  matrix(0, 3) = 0.6;
    matrix(1, 0) = 0.2;  matrix(1, 1) = 0.2;  matrix(1, 2) = 0.2;  matrix(1, 3) = 0.8;
    matrix(2, 0) = -0.6; matrix(2, 1) = 0;    matrix(2, 2) = 0.2;  matrix(2, 3) = 1;
    matrix.Print();
    /*  0 0.4 0.2 0.6
        0.2 0.2 0.2 0.8
        -0.6 0 0.2 1    */
    std::cout << std::endl;
    matrix.GaussJordan();
    matrix.Print();
    /*  0.2 0.2 0.2 0.8
        0 0.6 0.8 3.4
        0 0 -0.333333 -1.66667   */
}

void TestRational()
{
    Matrix<Rational> matrix(3, 4);
    matrix(0, 0) = 0;   matrix(0, 1) = Rational(2, 5);   matrix(0, 2) = Rational(1, 5);   matrix(0, 3) = Rational(3, 5);
    // matrix(1, 0) = Rational(1, 5);  matrix(1, 1) = Rational(1, 5);   matrix(1, 2) = Rational(1, 5);   matrix(1, 3) = Rational(4, 5);
    // matrix(2, 0) = Rational(-3, 5); matrix(2, 1) = Rational(0, 5);   matrix(2, 2) = Rational(1, 5);   matrix(2, 3) = Rational(1);
    //std::cout<<matrix(1, 0)<<std::endl;
    matrix.Print();
    /*  0 2/5 1/5 3/5
        1/5 1/5 1/5 4/5
        -3/5 0 1/5 1    */
    std::cout << std::endl;
    matrix.GaussJordan();
    matrix.Print();
    /*  1/5 1/5 1/5 4/5
        0 3/5 4/5 17/5
        0 0 -1/3 -5/3    */
}

int main()
{
    TestDouble();
    
    TestRational();
}

