#include <iostream>
#include "ring.h"
using namespace std;


int main(int argc, char const *argv[]) {
  ring<int> boyao(3);

  boyao.plus(5).plus(3).plus(1);
  boyao.print();

  for (ring<int>::iterator it = boyao.begin(); it != boyao.end(); it++) {
    std::cout << *it << '\n';
  }

  for(auto value: boyao) //operator++() not operator++(int)
  {
    std::cout << value << '\n';
  }

  std::cout << "*****************" << '\n';

  boyao.testLearn();

  return 0;
}
