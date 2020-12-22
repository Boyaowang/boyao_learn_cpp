#include <iostream>
using namespace std;

class calcPlus {
private:
  /* data */

public:
 calcPlus(){
   std::cout << "calcPlus" << '\n';
 };
 calcPlus(string name){
   std::cout << "name in plus is " << name << '\n';
 }
 int add(int a, int b){return a+b;};
virtual ~calcPlus (){};
};

template<typename calc>
class calcMinus:public calc {
private:
  /* data */

public:
  calcMinus(){
    std::cout << "calcMinus" << '\n';
  };
  calcMinus(string name):calc(name){
    std::cout << "name in minus is " <<name << '\n';
  }
  int minus(int a, int b){return a-b;};
  virtual ~calcMinus (){};
};


template<typename calc>
class calcDivideMuti:public calc {
private:

public:
  calcDivideMuti (){
  };
  calcDivideMuti(string name):calc(name){
    std::cout << "name is " << name << '\n';
  }
  double divide(double a, double b){return a/b;};
  virtual ~calcDivideMuti (){};
};

typedef calcDivideMuti<calcMinus<calcPlus>> myCalc;

int main(int argc, char const *argv[]) {
  myCalc test("zixin");
  std::cout << test.add(1,8) << '\n';
  calcDivideMuti<calcPlus> test2;
  return 0;
}
