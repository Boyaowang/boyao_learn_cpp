// "this" keyword example
// remember "this" is only in this class

#include <iostream>
using namespace std;

// declaration of the class "boyao"
class boyao;

void printFunctionValue(boyao& obj);

class boyao
{
public:
  int a, b;
  boyao(int a, int b)
  {
    this->a =a; // or (*this).a=a;
    this->b =b;
    printFunctionValue(*this);
    printItMyself(*this);
  };
  void printItMyself(boyao &obj)
  {
    std::cout << "a is equal to: "<< obj.a << '\n';
    std::cout << "b is equal to: " << obj.b << '\n';
  };
};

void printFunctionValue(boyao& obj)
{
  std::cout << "a is equal to: "<< obj.a << '\n';
  std::cout << "b is equal to: " << obj.b << '\n';
};

int main(int argc, char const *argv[]) {
  boyao Boyao(20,30);
  return 0;
}
