#include <iostream>

int factorial(int a)
{
  if (a==1) {
    return 1;
  } else {
    std::cout << "/* message */" << '\n';
    return a*factorial(a-1);
  }
}

int main(int argc, char const *argv[]) {
  std::cout << factorial(5) << '\n';
  return 0;
}
