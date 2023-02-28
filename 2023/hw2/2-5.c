#include <stdio.h>
int a[9][9];
int check;
int prime_list[]={0,2, 3, 5, 7, 11, 13, 17, 19, 23};

int checkOneNumber(int (*board)[9], int row, int col)
{
  int now = board[row][col];
  if(row - 1 >= 0 && col - 2 >= 0 && board[row - 1][col - 2] == now)  return 0;
  if(row - 2 >= 0 && col - 1 >= 0 && board[row - 2][col - 1] == now)  return 0;
  if(row - 2 >= 0 && col + 1 < 9 && board[row - 2][col + 1] == now)  return 0;
  if(row + 1 < 9 && col + 2 < 9 && board[row + 1][col + 2] == now)  return 0;
  if(row + 2 < 9 && col + 1 < 9 && board[row + 2][col + 1] == now)  return 0;
  if(row - 1 >= 0 && col + 2 < 9 && board[row - 1][col + 2] == now)  return 0;
  if(row + 2 < 9 && col - 1 >= 0 && board[row + 2][col - 1] == now)  return 0;
  if(row + 1 < 9 && col - 2 >= 0 && board[row + 1][col - 2] == now)  return 0;
  return 1;
}
int main()
{
  freopen("a.in","r",stdin);
  for(int i = 0; i < 9; ++i)
  {
    for(int j = 0; j < 9; ++j)
    {
      scanf("%d", &a[i][j]);
    }
  }
  for(int i = 0; i < 9; ++i)
  {
    check = 1;
    for(int j = 0; j < 9; ++j)
    {
      check *=  prime_list[a[i][j]];
      
    }
    if(check != 223092870)
    {
      
      printf("0\n");
      return 0;
    }
  }

  for(int i = 0; i < 9; ++i)
  {
    check = 1;
    for(int j = 0; j < 9; ++j)
    {
      check *=  prime_list[a[j][i]];
    }
    if(check != 223092870)
    {
      printf("0\n");
      return 0;
    }
  }

  for(int x = 0; x < 3; ++x)
  {
    for(int y = 0; y < 3; ++y)
    {
      check = 1;
      for(int i = x * 3; i < (x + 1) * 3; ++i)
      {
        for(int j = y * 3; j < (y + 1) * 3; ++j)
        {
          check *= prime_list[a[i][j]];
        }
      }
      
      if(check != 223092870)
      {
       printf("0\n");
        return 0;
      }
    }
  }

  for(int i = 0; i < 9; ++i)
  {
    for(int j = 0; j < 9; ++j)
    {
      if(!checkOneNumber(a, i, j)){
        printf("0\n");
        return 0;
      }
    }
  }
  printf("1\n");
  return 0;
}