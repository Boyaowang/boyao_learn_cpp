#include <iostream>
using namespace std;

namespace foam{
class Plus
{
public:
  int plus(int a, int b)
  {
    return a+b;
  }
};

template<class calcType>
class MultPlus
:public calcType
{
public:
  int mult(int a, int b)
  {
    return a*b;
  }
};

template<class calcType>
class DivideMultPlus
:public calcType
{
public:
  int divide(int a, int b)
  {
    return a/b;
  }
};

template<class calcType>
class MinusDivideMultPlus
:public calcType
{
public:
  int minus(int a, int b)
  {
    return a-b;
  }
};

};

namespace foam{
typedef MinusDivideMultPlus<DivideMultPlus<MultPlus<Plus>>> calculator;
};

int main(int argc, char const *argv[]) {
  foam::calculator a;
  std::cout << a.plus(1,5) << '\n';
  std::cout << a.mult(1,5) << '\n';
  std::cout << a.divide(1,5) << '\n';
  std::cout << a.minus(1,5) << '\n';
  return 0;
}
