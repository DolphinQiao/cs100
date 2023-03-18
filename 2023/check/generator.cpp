#include <iostream> 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <windows.h>
using namespace std;
//ofstream cout("data.in");
int main()
{
	srand(time(0));
//	srand( (unsigned)time( NULL ) );
	//freopen("input.txt","w",stdout); 
	int a;
	a=rand()%100 + 1;
	for(int i = 1; i <= a; ++i)
	{
		if(rand()%2 == 0)
		{
			printf("%c",rand()%26+'a');
		}else{
			printf("%c",rand()%26+'A');
		}
	}
	printf("\n");
	
	a = rand() * rand() * rand() % 1000000 + 1;
	for(int i = 1; i <= a; ++i)
	{
		if(rand()%2 == 0)
		{
			printf("%c",rand()%26+'a');
		}else{
			printf("%c",rand()%26+'A');
		}
	}
	return 0;
}