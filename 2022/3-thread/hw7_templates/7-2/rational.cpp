#include "rational.hpp"
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
  return os << number.m_numerator << "/" << number.m_denominator;
}
// int main()
// {
//     Rational a(-6, 10);
//     Rational b(1, 7);
//     std::cout << a << " " << a+b << " " << b-a << " " << b/a << std::endl;
//     // -3/5 -16/35 26/35 -5/21
//     return 0;
// }

