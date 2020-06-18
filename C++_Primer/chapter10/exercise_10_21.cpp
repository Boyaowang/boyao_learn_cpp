#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
  int a =5;
  auto func = [](int &a)
  ->bool
  {
    while (a>0) {
      a--;
    }
    return true;
  };
  std::cout << func(a) << '\n';
  std::cout << a << '\n';
  return 0;
}
