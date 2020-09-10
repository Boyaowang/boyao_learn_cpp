#include <iostream>
using namespace std;

class parants {
private:
  int a=1;

public:
  parants ()=default;
  virtual ~parants (){};
  virtual void print() = 0;
};

class child1:public parants {
private:
  /* data */

public:
  friend class parants;
  child1 ()=default;
  virtual ~child1 (){};
  virtual void print()
  {
    std::cout << "/* message */" << '\n';
    //helloWorld();
  }
  void helloWorld() {
    std::cout << "helloWorld" << '\n';
  }

};


int main(int argc, char const *argv[]) {
  child1 boyao;
  parants* P1 = new child1();
  return 0;
}
