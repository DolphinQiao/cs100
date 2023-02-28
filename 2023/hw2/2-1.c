#include <stdio.h>
#define N 110
#define ll long long
ll a[N];
int x;
int n;
int main()
{
  freopen("a.in", "r", stdin);
  scanf("%d", &n);
  int num = 0;
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d", &x);
    if(x > 0)
    {
      ++num;
      a[num] = 1ll * x * x;
    }
  }
  
  for(int i = num; i >= 1; --i)
  {
    printf("%lld\n", a[i]);
  }
  printf("%d\n", num);

  return 0;
}