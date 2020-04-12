#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {

  int a[4];
  int* b = &a[0];

  std::cout << b << '\n';


  return 0;
}
