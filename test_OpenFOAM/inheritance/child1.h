#ifndef CHILD1_H_
#define CHILD1_H_
#include "base.H"

#include <iostream>
using namespace std;

class child1:public Base {
private:
  /* data */

public:
  child1 (){
    cout << "constructor of child1" << '\n';
  };
  virtual ~child1 (){};
};

#endif
