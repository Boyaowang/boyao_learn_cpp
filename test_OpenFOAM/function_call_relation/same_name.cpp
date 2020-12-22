#include <iostream>
using namespace std;

class func1 {
private:
  /* data */

public:
  func1 (){};
  virtual ~func1 (){};
  void print() {
    std::cout << "This is function 1" << '\n';
  }
  func1 testWhichPrint()
  {
    return *this;
  }
};

class test:public func1 {
private:
  /* data */

public:
  test (){};
  virtual ~test (){};
};

class func2 {
private:
  test obj;

public:
  func2 (){};
  virtual ~func2 (){};
  void print() {
    std::cout << "This is function 2" << '\n';
  }

  func1 testWhichPrint()
  {
    return obj.testWhichPrint();
  }

};



int main(int argc, char const *argv[]) {
  func2 obj;
  obj.testWhichPrint().print();
  return 0;
}
