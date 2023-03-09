#include <stdio.h>
#define ll long long
ll num1, num2;
ll max,max_id,n;
ll tmp, con = 0;
int main()
{
  freopen("a.in", "r", stdin);
  scanf("%lld\n", &n);
  for(int i = 1; i <= n; ++i)
  {
    scanf("(%*[^,], %lld, %lld)\n", &num1, &num2);
    if(con - num1 <= 0)
    {
      con += num1;
      //con = 0;
      tmp = num2;

    }else{
      if(tmp == num2) con += num1;
      else con -= num1;
    }
  }
  printf("%lld\n",tmp);

  return 0;
}