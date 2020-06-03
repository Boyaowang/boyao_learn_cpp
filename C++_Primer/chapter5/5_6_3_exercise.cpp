#include <iostream>
using namespace std;
int a =10;
void divide(void)
{
  double a,b;
  std::cout << "input a and b " << '\n';
  std::cin >> a >> b;
  try{
    if (b==0) {
      throw runtime_error("the denominator is 0");
    }
  }catch(runtime_error err){
    std::cout << err.what() << '\n';
    std::cout << "b cannot be 0, please input another sets of value " << '\n';
    std::cin >> a >> b;
  }
  std::cout << "a/b = "<< a/b << '\n';
  std::cout << "This a is defined at global scope, which is equal to "<< ::a << '\n';
}

int fac(istream& a)
{
  int b;
  a >> b;
  int fac_a=1;
  while (b>1) {
    fac_a *= b--;
  }
  return fac_a;
}

int sfunc()
{
  static int svalue; // will be initialized to 0
  std::cout << svalue++ << '\n';
}

int main(int argc, char const *argv[]) {
  //divide();
  //int value;
//  std::cout << fac(std::cin) << '\n';
  for (size_t i = 0; i < 10; i++) {
    sfunc();
  }
  return 0;
}
