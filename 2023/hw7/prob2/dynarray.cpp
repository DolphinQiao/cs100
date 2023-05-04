#include "dynarray.hpp"
#include <iostream>
int main()
{
  int arr[] = {1, 2, 3, 5};
  Dynarray a(arr, arr + 4);
  Dynarray b{3};
  if(a>b) std::cout<<"YES\n";
  std::cout << a << '\n' << b << std::endl;
  return 0;
}