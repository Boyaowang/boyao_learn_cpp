#include <iostream>
#include "changeop.h"
using namespace std;

int main(int argc, char const *argv[]) {
  changeop a(20);
  changeop b(30);
  changeop c;
  c=c+b+a+a;
  std::cout << a.num << '\n';
  std::cout << c.num << '\n';
  changeop d=a.add(b).add(c).add(c);
  std::cout << d.num << '\n';
  return 0;
}
