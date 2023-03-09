#include <stdio.h>
#include <string.h>
char s[11];
int r, c, q, m[550][550], x;
int flag[550][550];
int pos_x, pos_y;
int direction[10][10];
/*
   3
 1 * 2
   4
*/
void Init()
{
  direction[1][3] = 1;
  direction[2][3] = 2;
  direction[3][3] = 3;
  direction[4][3] = 4;
  direction[1][1] = 4;
  direction[2][1] = 3;
  direction[3][1] = 1;
  direction[4][1] = 2;
  direction[1][2] = 3;
  direction[2][2] = 4;
  direction[3][2] = 2;
  direction[4][2] = 1;
  direction[1][4] = 2;
  direction[2][4] = 1;
  direction[3][4] = 4;
  direction[4][4] = 3;
}

int main()
{
  freopen("a.in","r",stdin);
  Init();
  scanf("%d%d%d",&r,&c,&q);
  for(int i = 1; i <= r; ++i)
  {
    for(int j = 1; j <= c; ++j)
    {
      scanf("%s", s);
      if(s[0] == 'L') m[i][j] = 1;
      else if(s[0] == 'R') m[i][j] = 2;
      else if(s[0] == 'U') m[i][j] = 3;
      else if(s[0] == 'D') m[i][j] = 4;
      //printf("%d ",m[i][j]);
      // 1 -> L    2 -> R     3 -> U    4 -> D
    }
  }

  scanf("%d%d", &pos_x, &pos_y);
  flag[pos_x][pos_y] = 1;
  for(int i = 1; i <= q; ++i)
  {
    scanf("%s", s);
    scanf("%d", &x);
    int dir = 0;
    if(strcmp(s, "Left") == 0)
    {
      dir = direction[m[pos_x][pos_y]][1];
    }else if(strcmp(s, "Right") == 0)
    {
      dir = direction[m[pos_x][pos_y]][2];
    }else if(strcmp(s, "Front") == 0)
    {
      dir = direction[m[pos_x][pos_y]][3];
    }else if(strcmp(s, "Back") == 0)
    {
      dir = direction[m[pos_x][pos_y]][4];
    }else{
      printf("Warning : Wrong type of string!!");
    }
    //printf("dir:%d\n",dir);
    //printf("x:%d\n",x);
    int flag1 = 0;
    if(dir == 1){
      if(pos_y - x >= 1 && flag[pos_x][pos_y - x] == 0)
      {
        flag1 = 1;
        pos_y -= x;
        flag[pos_x][pos_y] = 1;
      }
      
    }else if(dir == 2){

      if(pos_y + x <= c&&flag[pos_x][pos_y + x] == 0)
      {
        flag1 = 1;
        pos_y += x;
        flag[pos_x][pos_y] = 1;
      }

    }else if(dir == 3){

      if(pos_x - x >=1 && flag[pos_x - x][pos_y] == 0)
      {
        flag1 = 1;
        pos_x -= x;
        flag[pos_x][pos_y] = 1;
      }
    }else{
      
      if(pos_x + 1 <= r && flag[pos_x + x][pos_y] == 0)
      {
        flag1 = 1;
        pos_x += x;
        flag[pos_x][pos_y] = 1;
      }
    }
    if(flag1 == 0)
    {
      printf("Mistake!");
      break;
    }else{
      printf("(%d, %d)\n", pos_x, pos_y);
    }
  }

  return 0;
}