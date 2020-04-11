#include <iostream>
#include "functions.h"

using namespace std;

int main(int argc, char const *argv[]) {

  int* p = new int(3);
  std::cout << "The memory address of p is "<< p << '\n';
  std::cout << "p is equal to: "<< *p << '\n';
  //delete p;
  int n;
  std::cout << "Please input a value for the size of the array: ";
  std::cin >> n;
  int *q = new int[n];
  for(int i=0; i<n; i++)
  {
    q[i]=i+1;
  }
  for(int i=0; i<n; i++)
  {
    std::cout << q[i] << '\n';
  }

// test the functions
  newvalue funcp;
  int* r=funcp.intarr(n);
  for(int i=0; i<n; i++)
  {
    r[i]=i+1;
  }
  for(int i=0; i<n; i++)
  {
    std::cout << r[i] << '\n';
  }

  funcp.deletesigle(p);
  funcp.deletearray(q);
  funcp.deletearray(r);


  return 0;
}
