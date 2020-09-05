#include <iostream>
using namespace std;

#ifndef AXINXIN
#define hello(x) std::cout << x << '\n'
#else
#define hello(x) std::cout << "it is not defined" << '\n';
#endif

void toDef(string name) {
  #define printName(s) std::cout << s << '\n';
  printName(name);
}

int main(int argc, char const *argv[]) {
  hello("zixin");
  toDef("zixin");
  printName("zixin");
  return 0;
}
