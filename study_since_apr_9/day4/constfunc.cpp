#include <iostream>
#include "boyao.h"
using namespace std;

int main(int argc, char const *argv[]) {
  boyao nonconstobj;
  const boyao constobj;
  nonconstobj.nonconst();
  constobj.constfunc();
  return 0;
}
