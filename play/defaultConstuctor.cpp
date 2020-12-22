#include <iostream>
using namespace std;

class testDefaultConstructor {
private:
  /* data */

public:
  testDefaultConstructor (string name){};
  void print(/* arguments */) {
    std::cout << "/* abababa */" << '\n';
  }
  virtual ~testDefaultConstructor (){};
};

int main(int argc, char const *argv[]) {
  testDefaultConstructor* test;
  test->print();
  return 0;
}
