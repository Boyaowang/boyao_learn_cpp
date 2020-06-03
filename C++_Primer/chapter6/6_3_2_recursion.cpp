#include <iostream>
using namespace std;

int factorial(int a)
{
  if (a>1) {
    return factorial(a-1)*a;
  }
  return 1;
}
int main(int argc, char const *argv[]) {
  std::cout << factorial(5) << '\n';
  return 0;
}
