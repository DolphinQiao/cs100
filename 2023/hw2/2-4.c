#include <stdio.h>
#include <math.h>
#define ll unsigned long long
ll x, m;
int main()
{
  freopen("a.in","r",stdin);
  scanf("%llu%llu", &x, &m);
  m++;
  int len = (int)(log(x) / log(2)) + 1;
  //printf("%d\n", len);
  //printf("%lld\n%lld\n", (x >> (m + 1)),((x >> (len - m + 1)) << (len - m + 1)));
  ll ans = (x >> m) | (x & ((1llu << m) - 1llu)) << (len - m);
  printf("%llu ", ans);
  for(int i = 0; i <= len; ++i)
  {
    if(((1llu << i) & ans) == (1llu << i))
    {
      printf("%d", i);
      break;
    }
  }
  return 0;
}
