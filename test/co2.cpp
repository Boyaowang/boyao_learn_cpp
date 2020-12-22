#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  double sugar = 99/8;
  int CO2_price = 120;
  int machine = 530;
  double cola = 105/6;
  double net = cola - sugar;
  // i for litre
  for (size_t i = 1;; i++) {
     if(i/48==0 && i>48)
     {
      CO2_price+=120;
    }
    if((machine+CO2_price)<(i*net))
    {
      std::cout << i/8 << '\n';
      break;
    }
    std::cout << CO2_price << '\n';
  }
  return 0;
}
