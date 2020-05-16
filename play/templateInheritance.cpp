#include <iostream>
using namespace std;

class plus {
public:
  int value;
  int Plus(int a, int b)
  {
    return a+b;
  }
};

template<class calculator>
class plusMinus:
public calculator {
public:
  plusMinus (){};
  virtual ~plusMinus (){};
  plusMinus& Mult(int n)
  {
  calculator::value*=n;
  };
};

template<class calculator>
class plusMinusDivide:public calculator {

public:
  plusMinusDivide (){};
  virtual ~plusMinusDivide (){};
};

typedef plusMinus<plus> calc;

template<class T>
class name {
private:
  T age;

public:
  name (T age):age(age){
    std::cout << age << '\n';
  };
  virtual ~name (){};
};



int main(int argc, char const *argv[]) {
  //name<int> zixin(5);
  name<string> zixin("wusui");
  return 0;
}
