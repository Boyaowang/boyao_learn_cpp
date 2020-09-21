#ifndef BASE_H_
#define BASE_H_

#include <iostream>
using namespace std;

class Base {
private:
  /* data */

public:
  Base (){
    cout << "constructor of Base" << '\n';
  };
  virtual ~Base (){};
};

#endif
