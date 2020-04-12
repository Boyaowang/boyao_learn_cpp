#include <iostream>
#include "boyao.h"
using namespace std;

void boyao::nonconst()
{
  std::cout << "This is not a const function" << '\n';
};

void boyao::constfunc() const{
  std::cout << "This is a constant function" << '\n';
};
