#include <iostream>
using namespace std;

//#define AXINXIN <==>  g++ -D AXINXIN

#define AXINXIN ==1

//#ifdef AXINXIN
#if 1 // #if 0
#define hello(x) std::cout << x << '\n'
#else
#define hello(x) std::cout << "AXINXIN is not defined" << '\n';
#endif

void toDef(string name) {
  #define printName(s) std::cout << s << '\n';
  printName(name);
}

#define multiPrint {\
  hello("zixin");\
  hello("xiaoboyao");\
}

// how to use ## concatenator
// show in

int main(int argc, char const *argv[]) {
  //hello("zixin");
  // toDef("zixin");
  // printName("zixin");
  multiPrint;
  return 0;
}
