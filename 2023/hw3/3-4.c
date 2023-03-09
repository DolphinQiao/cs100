#include <stdio.h>
#define ll long long
int n, class; char ch[11000000];
int sum, cost;
int map[1100000];
int main()
{
  freopen("a.in", "r", stdin);
  scanf("%d", &n);
  int max = 0, max_id = 0;
  for(int i = 1; i <= n; ++i)
  {
    scanf("%[^,],%d,%d)", ch, &cost, &class);
    map[class] += cost;
    if(map[class] > max)
    {
      max = map[class];
      max_id = class;
      //printf("%d %d\n",max, max_id);
    }
  }
  // for(int i = 0; i <= 1000000; ++i)
  // {
  //   if(map[i] >= (sum + 1) / 2ll)
  //   {
  //     printf("%d\n",i);
  //     return 0;
  //   }
  // }
  printf("%d\n",max_id);
  return 0;
}