#include <iostream>
#include <memory>
using namespace std;

class father {
private:
  /* data */

public:

  virtual ~father (){};
    virtual void print() = 0;

};

class child1: public father{
private:
  /* data */

public:
  child1 (){};
  virtual ~child1 (){};
  virtual void print(/* arguments */) {
    std::cout << "child1" << '\n';
  }
};

class toTest {
private:
  /* data */

public:
  toTest (){};
  virtual ~toTest (){};
};


int main(int argc, char const *argv[]) {
  child1 axin;
  father& boyao(axin);
  boyao.print();

  return 0;
}
