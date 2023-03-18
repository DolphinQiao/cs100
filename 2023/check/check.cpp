#include<iostream>
#include<windows.h>
using namespace std;
int main()
{
	//int t=200;
    while(1)
    {
//    	t--;
        system("generator.exe > a.in");
        system("std.exe < a.in > std.txt");
         system("test.exe < a.in > ans.txt");
        if(system("fc ans.txt std.txt"))   break;
    }
    cout<<"error"<<endl;
    //system("pause");
    return 0;
}