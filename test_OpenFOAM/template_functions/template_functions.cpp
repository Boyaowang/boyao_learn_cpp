#include <iostream>
using namespace std;

template<typename T>
class child1 :public T{
private:


public:
  int a1 =1;
  child1 (){
    std::cout << "child1" << '\n';
  };
  virtual ~child1 (){};
  void printa1() {
    std::cout << a1 << '\n';
  }
};

template<typename T>
class child2 :public T{
private:


public:
  int a2 =2;
  child2 (){};
  virtual ~child2 (){};
  void printa2() {
    std::cout << a2 << '\n';
  }
  template<typename T2>
  void print_a4() {
    //T2::printab();
    T2::printa2();
  }
  // void print_a4() {
  //   T::printa();
  // }
};

template<typename T>
class child3 :public T{
private:


public:
  int a3 =3;
  child3 (){};
  virtual ~child3 (){};
  void printa3() {
    std::cout << a3 << '\n';
  }
};

template<typename T>
class child4 :public T{
private:


public:
  int a4 =4;
  child4 (){};
  virtual ~child4 (){};
  void printa4() {
    std::cout << a4 << '\n';
  }
};

class Base {
private:


public:
  int a =99999999;
  Base (){};
  virtual ~Base (){};
  void printab() {
    std::cout << a << '\n';
  }
};

typedef child2<child1<Base>> child2_to_child1_to_base;
typedef child4<child3<child2<child1<Base>>>> child4_to_child_3_to_child2_to_child1_to_base;


int main(int argc, char const *argv[]) {
  // child2_to_child1_to_base boyao;
  // Base& boyao2 = boyao;
  // boyao.printa();
  // boyao2.printa();
  child4_to_child_3_to_child2_to_child1_to_base boyao;
  boyao.print_a4<child2_to_child1_to_base>();
  return 0;
}
