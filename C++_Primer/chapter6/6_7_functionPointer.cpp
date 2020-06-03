#include <iostream>
using namespace std;

int Plus(int a, int b)
{
  return a;
}

typedef int pplus1(int,int);
typedef int (*pplus2)(int,int);

void combine(int a, int b, pplus1 func) {
  std::cout << func(a,b) << '\n';
}

pplus1 *test(){};
pplus2 test2(){};
// void combine2(int a, int b, printnew) {
//   std::cout << *printnew(a) << '\n';
// }

int main(int argc, char const *argv[]) {
  combine(1,2,Plus);
  return 0;
}
