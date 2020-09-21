#include <iostream>
#include <memory>
using namespace std;

class father {
private:
  /* data */

public:
  father (){};
  virtual ~father (){};
  virtual void print(/* arguments */) {
    std::cout << "father" << '\n';
  }
};

class child1: public father{
private:
  /* data */

public:
  child1 (){};
  virtual ~child1 (){};
  // virtual void print(/* arguments */) {
  //   std::cout << "child1" << '\n';
  // }
};

class child2: public father{
private:
  /* data */

public:
  child2 (shared_ptr<father> obj):newchild2(obj){};
  virtual ~child2(){};
  shared_ptr<father> newchild2;
  virtual void print(/* arguments */) {
    std::cout << "child2" << '\n';
  }
  void printNewChild2(/* arguments */) {
    newchild2->print();
  }
};


int main(int argc, char const *argv[]) {
  child1 boyao;
  child2 axin(make_shared<child1>(boyao));
  axin.printNewChild2();
  // shared_ptr<father> newboyao(make_shared<child1>(boyao));
  // newboyao->print();
  return 0;
}
