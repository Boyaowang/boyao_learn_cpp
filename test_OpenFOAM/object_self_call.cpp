#include <iostream>
#include <tuple>
#include <memory>
using namespace std;


class Base {
private:
  string name;

public:
  Base (){};
  Base(std::initializer_list<tuple<string, int>>){}
  Base(string name, int num){};

  class child {
  private:
    /* data */

  public:
    child(){};
    child (int num1){};
    virtual ~child (){};
  };

  child boyaowang;

  child return_child()
  {
    return boyaowang;
  }

  child operator()()
  {
    return this->return_child();
  }
  void print(/* arguments */) {
    /* code */
  }
  virtual ~Base (){};
};

int main(int argc, char const *argv[]) {
  tuple<string, int> someVal("constants",  42);
  Base axin({someVal});
  Base boyao();
  int a =10;
  //shared_ptr<Base::child>(axin()(a));
  return 0;
}
