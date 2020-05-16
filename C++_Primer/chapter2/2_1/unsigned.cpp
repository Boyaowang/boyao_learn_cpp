#include <iostream>
#include "variabels.h"
using namespace std;

double applyDiscount(int price, double discount)
{
  return static_cast<double>(price*discount);
}
int i=42;
int main(int argc, char const *argv[]) {
  // for (unsigned u = 10; u > 0; --u) std::cout << u << std::endl;
  // int a = -10ll;
  // std::cout << "\7" <<a << '\?' << '\n';
  //
  // char longlit = L'a';
  // std::cout << longlit << typeid(longlit).name()<< '\n';
  //
  // int price =5;
  // double discount = 0.5;
  // std::cout << applyDiscount(price,discount) << '\n';
  int alpha =1;
  std::cout << "global alpha "<<::alpha << " local alpha "<< alpha<< '\n';
  std::cout << ::_ << '\n';

  int i =100;
  int j= ::i;
  std::cout << j << '\n';
  extern int buffersize;
  extern const int &rdvalue;
  extern const int &rbuffer;
  buffersize =1000;
  std::cout << rbuffer << '\n';


  return 0;
}
