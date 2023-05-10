#include "polynomial.hpp"
#include <list>
#include <deque>
#include <cstdio>
int main()
{
  double a[] = {1, 2, -1, 3.5};
  std::vector b{2.5, 3.3, 0.0};
  std::list c{2.7, 1.828, 3.2}; // not a vector, but have iterators
  std::deque<double> d; // empty
  Polynomial p1(a, a + 4); // 1 + 2x - x^2 + 3.5*x^3
  Polynomial p2(std::vector{2.5, 3.3, 0.0}); // 2.5 + 3.3x, the trailing zero removed
  Polynomial p3(std::vector{2.5, 3.3, 0.0}); // 2.7 + 1.828x + 3.2*x^2
  Polynomial p4(d.begin(), d.end()); // 0
  Polynomial p5{0};
  printf("%lld\n", p5.deg());
  printf("%f\n", (p1*p5)[0]);
  printf("%.6f\n", (p1*p4)[1]);
  printf("%lld\n", (p1*p4).deg());
  printf("%.6f\n", (p1*p3)[2]);
  printf("%.6f\n", (p1*p3)[3]);
  return 0;
}