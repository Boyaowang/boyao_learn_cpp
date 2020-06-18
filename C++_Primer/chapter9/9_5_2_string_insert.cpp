#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
  string hello = "hello", world = "world ";
  hello.insert(0,world,0,world.size()-3);
  std::cout << hello << '\n';
  std::cout << world.size() << '\n';
  return 0;
}
