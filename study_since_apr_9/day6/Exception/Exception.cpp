#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {

//Exception 1
  try{
    int mom = 100;
    int son = 80;
    if (mom<son) {
      throw 99;
    }
  }catch(int x)
  {
    std::cout << "mom should be older than son!! ERROR "<< x << '\n';
  }
  // Exception 2
  try{
     int a =1;
      throw 99;
  }catch(int x)
  {
    std::cout << "mom should be older than son!! ERROR "<< x << '\n';
  }

  // Exception 3: a simple calculator
  try{
    int num1;
    std::cout << "input a value:" << '\n';
    std::cin >> num1;

    int num2;
    std::cout << "input another value:" << '\n';
    std::cin >> num2;

    if (num2==0) {
      throw 999;
    }

    std::cout << "The result is: "<< num1/num2 << '\n';

  }catch(int x)
  {
    std::cout << "The denominator cannot be zero, ERROR "<< x << '\n';
  }

  /*catch(...)
  {
    std::cout << "The denominator cannot be zero" << '\n';
  }*/

  return 0;
}
