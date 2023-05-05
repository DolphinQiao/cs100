#include "dynarray.hpp"
#include <iostream>
int main()
{
  int arr[] = {1, 2, 3, 5};
  Dynarray a(arr, arr + 4);
  Dynarray b(arr + 1, arr + 3);
  Dynarray c;
  if(a < b) std::cout<<"YES\n";
  std::cout<<a<<"\n"<<b;
  return 0;
}