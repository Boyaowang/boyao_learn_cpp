#include <iostream>
#include "complex.H"

using namespace std;
using namespace boyaoCalc;

int main(int argc, char const *argv[]) {
  complex test1(2,1);
  complex test2 = test1;
  complex test3 = test1+test2;
  std::cout << test3+complex(1,1) << '\n';
  return 0;
}
