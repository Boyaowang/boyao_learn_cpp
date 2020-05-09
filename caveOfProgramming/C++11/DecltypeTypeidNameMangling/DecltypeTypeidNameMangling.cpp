#include <iostream>
#include <typeinfo> //for typeid
using namespace std;

class boyao{
public:
  boyao(){};
};

class jiechen{
public:
  jiechen(){};
};

int main(int argc, char const *argv[]) {

  int value;
  double dvalue;
  string name;
  boyao Boyao;
  jiechen Jiechen;

  std::cout << typeid(value).name() << '\n';
  std::cout << typeid(name).name() << '\n';
  std::cout << typeid(dvalue).name() << '\n';

  decltype(value) Value = 10;
  decltype(Jiechen) zixin;

  std::cout << typeid(Value).name() << '\n';
  std::cout << typeid(Boyao).name() << '\n';
  std::cout << typeid(Jiechen).name() << '\n';


  return 0;
}
