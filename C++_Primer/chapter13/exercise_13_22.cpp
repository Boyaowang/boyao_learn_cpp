#include <iostream>
using namespace std;

class HasPtr {
private:
  string *ps;
  int i;
public:
  HasPtr(const string s):ps(new string(s)),i(0){};
  HasPtr(const HasPtr &hp):ps(new string(*hp.ps)),i(hp.i){};
  HasPtr &operator=(HasPtr &rhs){
    auto new_ps=new string(*rhs.ps);
    delete ps;
    ps = new_ps;
    i = rhs.i;
    return *this;
  };
  virtual ~HasPtr (){delete ps;};
};
int main(int argc, char const *argv[]) {

  return 0;
}
