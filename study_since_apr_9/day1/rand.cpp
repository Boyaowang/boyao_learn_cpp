#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char const *argv[]) {
  int a= time(0);
  srand(a);
  std::cout << "Time(0) is "<< a << '\n';
  std::cout << rand() << '\n';
  return 0;
}
