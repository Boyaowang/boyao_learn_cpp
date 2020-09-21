#include <iostream>
using namespace std;

#ifndef AXINXIN
#define hello(x) toDef(x)
#else
#define hello(x) std::cout << "it is not defined" << '\n'
#endif


void toDef(string name) {
  #define printName(s) std::cout << s << '\n';
  printName(name);
}

// check if Macro is running when the class object is just defined
#ifndef AXINXIN2
#define heihei(name,hehe) void print##hehe(){std::cout << name << '\n';}
#endif

  class Macro_in_class {
  private:
    string name;

  public:
    Macro_in_class (){};
    Macro_in_class (string name):name(name){};
    heihei(name,gouzi);
    virtual ~Macro_in_class (){};
  };

  typedef int INT;

  typedef std::conditional<true,int,float>::type A;


int main(int argc, char const *argv[]) {
  hello("zixin");
  toDef("zixin");
  printName("zixin");
  Macro_in_class gouzi("gouzi");
  gouzi.printgouzi();
  A a = 6666;
  std::cout << a << '\n';
  return 0;
}
