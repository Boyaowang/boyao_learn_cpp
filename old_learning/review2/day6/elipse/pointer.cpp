#include <iostream>

int main(int argc, char const *argv[]) {
  int a=4;
  auto* b=&a;
  cout << "depointer b "<< *b << '\n';
  return 0;
}
