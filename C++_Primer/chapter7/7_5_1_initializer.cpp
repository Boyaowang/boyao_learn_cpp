#include <iostream>
using namespace std;

class toUse {
private:
  /* data */

public:
  toUse (int a){};
  virtual ~toUse (){};
};

class test {
private:
  const int cvalue;
  int& rvalue;
  toUse boyao;
  string svalue;

public:
  test() =default;
  test (int a):cvalue(a),rvalue(a),boyao(a){};
  virtual ~test ();
};

int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
