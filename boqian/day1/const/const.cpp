#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {

  const int a = 10; // const value
  std::cout << "The value of a is equal to "<< a << '\n';
  int q=const_cast<int&>(a) = 6;
  std::cout << "The value of a is equal to "<< q << '\n';
  int aa =9;

  const int* b = &a; //data is const, pointer is not
  std::cout << b << " \nThe value is "<<*b << '\n';
  b++;
  std::cout << b << " \nThe value is "<<*b << '\n';

  int* const c = &aa; //pointer is const, data is not
  const int* const d = &a; // both data and pointer are const

  // Most important:
  // If const is on the left side of the *, data is const
  // If const is on the right side of the *, pointer is const
  int j=1;
  int e= static_cast<const int&>(j);
  j=5;
  std::cout << j << '\n';
  return 0;
}
