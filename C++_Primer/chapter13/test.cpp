#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  int a =10;
  for (size_t i = 0; i < 5; i++) {
    if (!a--) {
    }
    std::cout << a << '\n';
  }
  return 0;
}
