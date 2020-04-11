#include <iostream>

void helloworld(){
  std::cout << "Hello world!!" << '\n';
}

int main(int argc, char const *argv[]) {
  auto boyao= helloworld;
  boyao();
  int c;

  return 0;
}
