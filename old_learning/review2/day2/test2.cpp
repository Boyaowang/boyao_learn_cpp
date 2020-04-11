#include <iostream>
using namespace std;

int testreturn(int a, int b){};

class boyao{
public:
  static int i;
  boyao(){};
  void increasei()
  {
    i++;
  }
};
int boyao::i=1;

int main(int argc, char const *argv[]) {
  boyao a;
  boyao b;
  std::cout << a.i << '\n';
  a.increasei();
  std::cout << b.i << '\n';
  return 0;
}
