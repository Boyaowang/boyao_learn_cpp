#include <iostream>
using namespace std;

class base {
private:
  /* data */

public:
  base (){};
  virtual ~base (){};
  int t = 1;
  int print()
  {
    return t;
  }

  template<typename Tchild>
  void name(Tchild &a) {
    a.usePrint();
    a.value = 5;
  }
};


template<typename T1>
class child1:public T1 {
private:


public:
  int value =10;
  child1 (){};
  virtual ~child1 (){};
  int a = this->t;
  int usePrint()
  {
    (*this).print();
    this->print(); // this .... child1<T1>
  }
  void printValue(/* arguments */) {
    std::cout << value << '\n';
  }

};

typedef child1<base> childuse;

int main(int argc, char const *argv[]) {
  child1<base> child111;
  child111.usePrint();

  childuse *child222;
  child222->usePrint();
  (*child222).usePrint();

  child111.printValue();
  base father;
  father.name(child111);
  child111.printValue();
  return 0;
}
