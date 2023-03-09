#include <stdio.h>
#include <string.h>

/*
将keyword 和 cipher 转换为全小写，并保留副本
将keyword 映射到 key 中
输出判断大小写
*/

#define N 1100000
char key[30];//key --> value
char key_rev[30];
int flag[30];
char keyword[110],low_keyword[110];
char cipher[N];
int main()
{
  freopen("a.in","r",stdin);

  scanf("%s\n", keyword);
  int num = 0;
  while(scanf("%c", &cipher[num])!=EOF) num++;
  

  memset(flag, 0, sizeof flag);
  int len_keyword = strlen(keyword);
  for(int i = 0; i < 30; ++i) key[i] = -1;
  for(int i = 0; i < len_keyword; ++i) low_keyword[i] = (keyword[i] >= 'A' && keyword[i] <= 'Z')?keyword[i]-'A':keyword[i]-'a';
  int cnt = 0;
  int pos = 0;
  int val = 0;
  for(int i = 0; i < len_keyword; ++i)
  {
    if(low_keyword[i] >= 0 && low_keyword[i] < 26)
    {
      if(flag[(int)low_keyword[i]] == 0){
        key[cnt] = (int)low_keyword[i];
        cnt++;
        val = (int)low_keyword[i];
        flag[(int)low_keyword[i]] = 1;
        pos = cnt;
      }
    }
  }
  
  //printf("%d\n",pos);
  
  while(pos < 26)
  {
    val++;
    while(flag[val % 26] == 1) val++;
    key[pos] = val % 26;
    pos++;
  }

  //for(int i = 0; i < 26; ++i) printf("%d ",(int)key[i]);

  for(int i = 0; i < 26; ++i)
  {
    
    for (int j = 0; j < 26; ++j)
    {
      if(key[i]==j) key_rev[j] = i;
    }
  }
  int len_cipher = strlen(cipher);
  for(int i = 0; i < len_cipher; ++i)
  {
    if(cipher[i] >= 'a' && cipher[i] <= 'z') printf("%c", key_rev[cipher[i] - 'a'] + 'a');
    else if(cipher[i] >= 'A' && cipher[i] <= 'Z') printf("%c", key_rev[cipher[i] - 'A'] + 'A');
    else printf("%c", cipher[i]);
  }

  return 0;
}