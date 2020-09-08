#include <iostream>
using namespace std;

template<typename T>
class child1 :public T{
private:


public:
  int a =999;
  child1 (){};
  virtual ~child1 (){};
  void printa() {
    std::cout << a << '\n';
  }
};

template<typename T>
class child2 :public T{
private:


public:
  int a =10;
  child2 (){};
  virtual ~child2 (){};
  void printa() {
    std::cout << a << '\n';
  }
};

class Base {
private:


public:
  int a =99999999;
  Base (){};
  virtual ~Base (){};
  void printa() {
    std::cout << a << '\n';
  }
};

typedef child2<child1<Base>> child2_to_child1_to_base;

int main(int argc, char const *argv[]) {
  child2_to_child1_to_base boyao;
  Base& boyao2 = boyao;
  boyao.printa();
  boyao2.printa();
  return 0;
}
