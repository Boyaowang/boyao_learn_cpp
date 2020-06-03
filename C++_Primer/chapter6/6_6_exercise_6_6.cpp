#include <iostream>
using namespace std;

void func(){};
void func(int a, int b) {
 std::cout << "2" << '\n';
}
void func(int a) {
  std::cout << "3" << '\n';
}
void func(double a, double b=1.1) {
 std::cout << "4" << '\n';
}

void constCall(const int& a){
  std::cout << a << '\n';
}

class clac {
private:
  int a=0;

public:
  clac (){};
  virtual ~clac (){};
clac& add(int value){
  this->a += value;
  return *this;
}

void get() {
  std::cout << a << '\n';
}
};

int main(int argc, char const *argv[]) {
  func(42.1, 1.2);
  int a =10;
  const int b = a+1;
  constCall(a);
  constCall(b);
  clac clactest;
  (clactest.add(50).add(15).add(33)).get();
  return 0;
}
