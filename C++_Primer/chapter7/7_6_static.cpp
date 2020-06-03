#include <iostream>
using namespace std;

class people {
private:
  static int amount;
  int age;
  static const int ivalue;

public:
  people (){};
  virtual ~people (){};

  static int totoalAmount(){
    return amount;
  };

  int print(int a =amount){};
};

int people::amount =10;
const int people::ivalue =10;// can also be defined inside the class if it is a const

int main(int argc, char const *argv[]) {
  auto a = people::totoalAmount();
  return 0;
}
