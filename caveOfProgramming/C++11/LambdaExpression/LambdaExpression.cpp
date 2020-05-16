#include <iostream>
using namespace std;

void callYourSelf(void(*pFunc)()) {
  pFunc();
}

void funcString(void(*pFunc)(string))
{
  pFunc("boyao");
}

void funcDivide(double(*pFunc)(double, double))
{
  std::cout << "a/b = " << pFunc(1,20) << '\n';
}

int main(int argc, char const *argv[]) {
  auto func = [](){std::cout << "hello" << '\n';};

  void(*func2)() = [](){std::cout << "hello2" << '\n';};

  //void(*func3)(string) = [](string name){std::cout << name << '\n';};

  auto func3 = [](string name){std::cout << name << '\n';};

  //[](){std::cout << "hello call myself" << '\n';}();

  double(*divide)(double,double) = [](double a, double b)-> double{
    if(b==0)
    {
      std::cout << "the denominator cannot be zero" << '\n';
      return 0;
    }
    return a/b;
  };

  funcString(func3);

  func();

  func2();

  callYourSelf([](){std::cout << "hello call myself" << '\n';});

  callYourSelf(func2);

  std::cout << divide(1,0) << '\n';

  funcDivide(divide);

  [](){std::cout << "age" << '\n';}();

  return 0;
}
