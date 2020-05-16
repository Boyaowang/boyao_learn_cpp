#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {

  [](){}(); // [](){} is an empty lambda function [](){}() when you want to call it

  int a = 0;
  int b = 1;
  int c = 2;

  // in [] you capture the variables
  [a, b, c](){std::cout << a << ", "<< b << ", "<< c << '\n';}();

  // capture all local variables with [=]
  [=](){std::cout << a << ", "<< b << ", "<< c << '\n';}();

  // capture all local variables with [=] but specify c
  [=, &c](){
    c = 999;
    std::cout << a << ", "<< b << ", "<< c << '\n';}();

  // capture all local variables in reference [&]
  [&](){
    a=333;
    b=666;
    c = 999;
    std::cout << a << ", "<< b << ", "<< c << '\n';}();

  // capture all local variables in reference [&], but b and c are not
    [&, b ,c](){
      a=33;
      //b=666;
      //c = 999;
      std::cout << a << ", "<< b << ", "<< c << '\n';}();
  return 0;
}
