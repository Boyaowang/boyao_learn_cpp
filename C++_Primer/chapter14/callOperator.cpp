#include <iostream>
using namespace std;

class callOp {
private:
  int value =10;
public:
  callOp (){};
  callOp (int a){};
  virtual ~callOp (){};
  int operator()(int a) &
  {
    return a;
  }

  int operator()(int a) &&
  {
    std::cout << "Rvalue " << endl;
    return a;
  }

  int returnValue()
  {
    return value;
  }

  void print(int a) & {
    std::cout << "Lvalue "<< a << '\n';
  }

  void printr(callOp &&a) && {
    std::cout << " rrr" << '\n';
  }

  void printr(callOp &&a) & {
    std::cout << "lll"<<a.value << '\n';
  }

};


int main(int argc, char const *argv[]) {
  callOp test;
  int a =1;
  int && b = test(11);
  test.print(test(1));
  test.print(test.returnValue());
  test.printr(callOp(999));
  return 0;
}
