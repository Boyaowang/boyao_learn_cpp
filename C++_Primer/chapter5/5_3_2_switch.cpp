#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  //int oddCnt =0 , evenCnt = 0;
  int value;

  while (std::cin >> value) {
    switch (value%2) {
      case 1:
      std::cout << "odd" << '\n';
      break;
      case 0:
      std::cout << "even" << '\n';
      break;
    }
  }
  return 0;
}
