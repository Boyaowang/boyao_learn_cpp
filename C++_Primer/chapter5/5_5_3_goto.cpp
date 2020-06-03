#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  int value;
  input_value:
  std::cin >> value;
  if (value!=10) {
    goto input_value;
  }else{
    std::cout << "10 is the input" << '\n';
  }
  return 0;
}
