#include <iostream>
using namespace std;

#define INT int
#define axin(x) std::cout << x << '\n';
#define print_something(x,type) void name##type() {\
  axin(x);\
}


print_something("axin",axinxin);
print_something("gouzi",gouzi);
print_something("zixin",zixin);

void numbers(int a = 10) {
  std::cout << a << '\n';
}

int main(int argc, char const *argv[]) {
  //axin("gouzi");
  nameaxinxin();
  namegouzi();
  namezixin();
  std::cout << __TIME__ << '\n';
  numbers();

  std::cout << "name""name" << '\n';
  return 0;
}
