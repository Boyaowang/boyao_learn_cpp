#include <iostream>
using namespace std;

template<class T>
void print(T obj) {
  std::cout << obj << '\n';
}

int main(int argc, char const *argv[]) {
  print("hehe");
  return 0;
}
