#include <iostream>
using namespace std;

class Boyao
{
protected:
  int a;
public:
  Boyao(int b):
  a(b){};
  void printvalue()
  {std::cout << "a is: "<< a << '\n';}
};

int main(int argc, char const *argv[]) {
  Boyao boyao(5);
  boyao.printvalue();
  // std::cout << boyao.a << '\n'; // this is impossible since a is protected;
  return 0;
}
