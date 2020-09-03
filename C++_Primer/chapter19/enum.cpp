#include <iostream>
using namespace std;

enum colors{black =999, blue, yellow};

void print(int color) {
  std::cout << color << '\n';
}

int main(int argc, char const *argv[]) {
  colors eye = black;
  colors eye2 = yellow;
  colors eye3 = eye2;
  std::cout << eye << " " << eye2 << '\n';
  int a = 999;
  print(eye3);

  return 0;
}
