#include <stdio.h>
#include <math.h>
#define eps 1e-5
int a, b, c;
double solution1, solution2;
int main()
{
  freopen("a.in","r",stdin);
  scanf("%d%d%d", &a, &b, &c);
  if(a == 0 && b == 0 && c == 0)
  {
    printf("x\\in\\mathbb{R}\n");
    return 0;
  }
  if(a == 0)
  {
    if(b == 0)
    {
      printf("No solution.");
      return 0;
    }
    solution1 = 1.0f * (-c) / b;
    printf("x = %.3f", solution1);
    return 0;
  }
  double delta = 1.0f * b * b - 4.0f * a * c;
  if(delta < 0)
  {
    printf("No solution.");
    return 0;
  }else
  {
    delta = sqrt(delta);
    double solution1, solution2;
    solution1 = 1.0f * ((-b) - 1.0f * delta)/ 2.0f / a;
    solution2 = 1.0f * ((-b) + 1.0f * delta)/ 2.0f / a;
    if(solution1 == solution2)
    {
      printf("x1 = x2 = %.3f", solution1);
      return 0;
    }else{

      if(solution1 < solution2) printf("x1 = %.3f, x2 = %.3f", solution1,solution2);
      else printf("x1 = %.3f, x2 = %.3f", solution2, solution1);
      return 0;
    }
  }
  return 0;
}