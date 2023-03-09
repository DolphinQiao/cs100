#include <stdio.h>
#include <string.h>

#define N 1100000
#define SQ26 11881376
#define SQ10 10000000
char cipher[N];
int n;
int main()
{
  freopen("a.in","r",stdin);

  scanf("%d\n", &n);
  int num = 0;
  while(scanf("%c", &cipher[num])!=EOF)++num;

  int len = strlen(cipher);
  for (int i = 0; i < len; ++i)
  {
    if(cipher[i] - '0' >= 0 && cipher[i] - '0' <= 9)
    {
      cipher[i] = '0' + (cipher[i] - '0' + SQ10 - n ) % 10;
    }
    if(cipher[i] >= 'a' && cipher[i] <= 'z')
    {
      cipher[i] = 'a' + (cipher[i] - 'a' + SQ26 - n ) % 26;
    }
    if(cipher[i] >= 'A' && cipher[i] <= 'Z')
    {
      cipher[i] = 'A' + (cipher[i] - 'A' + SQ26 - n ) % 26;
    }
  }
  printf("%s",cipher);
  return 0;
}