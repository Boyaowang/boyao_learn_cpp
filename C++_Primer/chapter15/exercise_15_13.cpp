using namespace std;
#include <iostream>

class base {
public:
  string name() { return basename; }
  virtual void print(ostream &os) { os << basename; }
private:
  string basename = "a";
};

class derived : public base {
public:
  void print(ostream &os) { base::print(os); os << " " << i; }
private:
  int i;
};
int main(int argc, char const *argv[]) {
  derived zixin;
  zixin.print(cout);
  return 0;
}
