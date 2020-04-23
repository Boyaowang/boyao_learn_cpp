#include <iostream>
using namespace std;

namespace foam{
class Plus
{
public:
  int value=0;
  int plus(int a, int b)
  {
    return a+b;
  };
  Plus& pluss(int n)
  {
    value+=n;
  };
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
  MultPlus& Mult(int n)
  {
    calcType::value*=n;
  };
};

template<class calcType>
class DivideMultPlus
:public calcType
{
public:
  int divide(int a, int b)
  {
    return a/b;
  };
  DivideMultPlus& Divide(int n)
  {
    calcType::value/=n;
  };
};

template<class calcType>
class MinusDivideMultPlus
:public calcType
{
public:

  int minus(int a, int b)
  {
    return a-b;
  };
  MinusDivideMultPlus& Minus(int n)
  {
    calcType::value-=n;
  };
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
  a.Minus(100).Divide(2).Mult(3).pluss(2);
  std::cout << a.value << '\n';
  return 0;
}
