#include <iostream>
#include <memory>
using namespace std;

class name;

class testDefaultConstructor {
private:
  /* data */

public:
  shared_ptr<name> zixin;
  testDefaultConstructor(string name){};
  //reset zixin
   void resetZixin(string yourname);
   void helloWorld(/* arguments */) {
     std::cout << "hellow world" << '\n';
   }
  void printName();
  virtual ~testDefaultConstructor(){};
};

class testDefaultConstructor2 {
private:
  shared_ptr<name> axinxin;

public:
  testDefaultConstructor2(string yourname):axinxin(nullptr){
     resetName(yourname);
  };
  void resetName(string inputName);
  void printName();
  virtual ~testDefaultConstructor2 (){};
};

class name {
private:
  string Name;

public:
  name (string name):Name(name){};
  void printName(/* arguments */) {
    std::cout << "your name is " << Name << '\n';
  }
  virtual ~name (){};
};

void testDefaultConstructor::resetZixin(string yourname)
{
   testDefaultConstructor::zixin.reset(new name(yourname));
}

void testDefaultConstructor::printName() {
  zixin->printName();
}

void testDefaultConstructor2::resetName(string inputName) {
  axinxin.reset(new name(inputName));
}

void testDefaultConstructor2::printName() {
  axinxin-> printName();
}

int main(int argc, char const *argv[]) {
   testDefaultConstructor axin2("zixin");
   axin2.resetZixin("axin");
   axin2.printName();
   testDefaultConstructor2 xiaomao("xiaomao");
   xiaomao.printName();
   //axin->printName();
  return 0;
}
