#include <iostream>
using namespace std;


int main(int argc, char const *argv[]) {
  int value;
  while (std::cin >> value) {
    if (value==67) {
      break;
    }
    std::cout << value << '\n';
  }
  return 0;
}
