#include <stdio.h>
#define N 110
int month_num, start, finish;
int month[N];

int check(int num)
{
  if(num / 10000000 != num % 10) return 0;
  if(num / 1000000 % 10 != num % 100 / 10) return 0;
  if(num / 100000 % 10 != num % 1000 / 100) return 0;
  if(num / 10000 % 10 != num % 10000 / 1000) return 0;
  return 1;
}
int main()
{
  freopen("a.in","r",stdin);

  scanf("%d ", &month_num);
  for(int i = 1; i <= month_num; ++i)
  {
    scanf("%d ",&month[i]);
  }

  scanf("%d%d",&start, &finish);

  int num = 0;
  for(int i = start; i <= finish; ++i)
  {
    int mon = i % 10000 / 100;
    if(mon == 0 || mon > month_num) continue;
    int day = i % 100;
    if(day == 0 || month[mon] < day) continue;
    if(check(i)) num++;
  }
  printf("%d\n",num);

  return 0;
}