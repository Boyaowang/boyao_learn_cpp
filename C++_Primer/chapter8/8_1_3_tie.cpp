#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  int a;
  ostream *p =cin.tie(&cout);
  std::cin >> a;
  *p << a << endl;
  std::cout << a << '\n';
  return 0;
}
