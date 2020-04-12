#include <iostream>
#include "boyao.h"
using namespace std;

int main(int argc, char const *argv[]) {
  boyao nonconstobj(6,5);
  const boyao constobj(7,5);
  nonconstobj.nonconst();
  constobj.constfunc();
  return 0;
}
