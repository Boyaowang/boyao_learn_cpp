#include <iostream>
using namespace std;

class base {
private:
  /* data */

public:
  base (){};
  virtual void  print() = 0;
  virtual ~base (){};
};

class child1:public base {
private:
  /* data */

public:
  child1 (){};
  void print() {
    std::cout << "child" << '\n';
  }
  virtual ~child1 (){};
  class grandChild1 {
  private:


  public:
    grandChild1 (){};
    virtual ~grandChild1 (){};
    grandChild1 operator()(){
      return *this;
    }
  };
};

int main(int argc, char const *argv[]) {
  child1 a;
  base& b = a;
  b.print();


  return 0;
}
