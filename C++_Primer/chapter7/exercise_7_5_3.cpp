#include <iostream>
#include <vector>
using namespace std;

class NoDefault {
private:

public:
  NoDefault() = default;
  NoDefault (int){};
  virtual ~NoDefault (){};
};

class C {
private:
  NoDefault mem;
public:
  C () =default;
  virtual ~C (){};
};

int main(int argc, char const *argv[]) {

  std::vector<C> vec(10);
  return 0;
}
