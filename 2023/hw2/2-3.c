#include <stdio.h>
#include <string.h>
char a[550], b[550], c, ans[550];
int main()
{
  freopen("a.in","r",stdin);
  c = getchar();
  scanf("%s", a);
  scanf("%s", b);
  // printf("%c\n",c);
  // printf("%lld %lld", strlen(a), strlen(b));
  
  int len_a = (int)strlen(a);
  int len_b = (int)strlen(b);

  // int len_min = len_a < len_b ? len_a : len_b;
  int len_max = len_a > len_b ? len_a : len_b;
  for(int i = 0; i < len_a; ++i)
  {
    if(a[i]>='0' && a[i]<= '9') a[i]-='0';
    if(a[i]>='a' && a[i]<= 'f') a[i]-='a'-10;
    //printf("%d ", a[i]);
  }
  for(int i = 0; i < len_b; ++i)
  {
    if(b[i]>='0' && b[i]<= '9') b[i]-='0';
    if(b[i]>='a' && b[i]<= 'f') b[i]-='a'-10;
  }

  int flag = 0;
  if(c=='-'&&(len_a < len_b || (len_a==len_b&&strcmp(a, b) < 0)))//a is smaller than b
  {
    flag = 1;
  }
  for(int i = 0; i < len_max; ++i)
  {
    if(c == '+') ans[i] = a[len_a - i - 1] + b[len_b - i - 1];
    if(flag==0&&c == '-') ans[i] = a[len_a - i - 1] - b[len_b - i - 1];
    if(flag==1&&c == '-') ans[i] = b[len_b - i - 1] - a[len_a - i - 1];
    //printf("%d ", ans[i]);
  }
  int up = 0;
  for(int i = 0; i < len_max; ++i)
  {
    
    if(ans[i] >= 0)up = ans[i] / 16;
    else{
      up = -1;
      ans[i] +=16;
    }
    ans[i + 1] += up;
    ans[i] %= 16;
    //printf("%d ", ans[i]);
  }
  int len_ans = a[len_max + 1] != 0? len_max + 1 : len_max;;
  len_max = len_max + 1;

  for(int i = 0; i < len_a; ++i)
  {
    if(a[i] < 10) a[i] += '0';
    else a[i] +='a' - 10;
  }
  for(int i = 0; i < len_b; ++i)
  {
    if(b[i] < 10) b[i] += '0';
    else b[i] +='a' - 10;
  }
  for(int i = 0; i < len_ans; ++i)
  {
    //printf("%d\n",ans[i]);
    if(ans[i] < 10) ans[i] += '0';
    else ans[i] += 'a' - 10;
  }

  for(int i = 0; i < len_max - len_a; ++i) printf(" ");
  for(int i = len_max - len_a; i <= len_max; ++i) printf("%c", a[i - (len_max - len_a)]);
  printf("\n");
  printf("%c",c);
  for(int i = 0; i < len_max - len_b - 1; ++i) printf(" ");

  for(int i = len_max - len_b; i <= len_max; ++i) printf("%c", b[i - (len_max - len_b)]);
  printf("\n");
  for(int i = 0; i < len_max; ++i) printf("-");
  printf("\n");
  if(flag == 0)for(int i = 0; i < len_max - len_ans; ++i) printf(" ");
  if(flag == 1){
    for(int i = 0; i < len_max - len_ans - 1; ++i) printf(" ");
    printf("-");
  }
  for(int i = len_ans + 1; i >= len_max - len_ans; --i) printf("%c", ans[i - (len_max - len_ans)]);

  return 0;
}