#include <iostream>
#include "boyao.h"
using namespace std;

// constructor
boyao::boyao(int a, int b):
regval(a),
constval(b)
{};

// destructor
boyao::~boyao()
{
  std::cout << "regval is: "<< regval << '\n';
  std::cout << "constval is: "<< constval << '\n';
};

void boyao::nonconst()
{
  std::cout << "This is not a const function" << '\n';
};

void boyao::constfunc() const{
  std::cout << "This is a constant function" << '\n';
};
