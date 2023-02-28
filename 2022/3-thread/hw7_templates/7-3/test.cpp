#include <thread>
#include <mutex>
#include <iostream>

int main()
{
  int num = std::thread::hardware_concurrency();
  std::cout<<num;
  return 0;
}