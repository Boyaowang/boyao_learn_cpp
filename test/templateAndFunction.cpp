#include <iostream>
using namespace std;

class calcPlus {

private:
public:
  calcPlus (){};

  template<class T>
  void solve(T a, T b)
  {
    std::cout << "a+b is "<< a+b << '\n';
  }

  virtual ~calcPlus (){};
};

template<class calc>
class calcMinus :public calc{
private:
  /* data */

public:
  calcMinus (){};

  template<class T>
  void solve(T a, T b)
  {
    std::cout << "a-b is "<< a-b << '\n';
  }

  virtual ~calcMinus (){};
};

template<class calc>
class calcMulti: public calc {
private:
  double a;
  double b;

public:
  calcMulti (double a, double b):a(a),b(b){};

  void print() {
      this->solve(a,b);
  }

  virtual ~calcMulti (){};
};

typedef calcMulti<calcMinus<calcPlus>> calculator;

int main(int argc, char const *argv[]) {
  calculator test(12,5.5);
  test.print();
  return 0;
}
