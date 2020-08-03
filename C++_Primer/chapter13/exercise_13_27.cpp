#include <iostream>
using namespace std;

class HasPtr {
private:
  string *ps;
  size_t *use;
  int i;

public:
  HasPtr(const string& s = string()):ps(new string(s)),use(new size_t(1)),i(0){};
  HasPtr(const HasPtr& rhs):use(rhs.use),i(rhs.i),ps(rhs.ps){
     (*use)++;
  };
  HasPtr &operator = (HasPtr &);
  virtual ~HasPtr (){
    if (*use == 0) {
      delete ps;
      delete use;
    }
  };

  void getUse(){
    std::cout << *use << '\n';
  }
};

HasPtr& HasPtr::operator = (HasPtr &rhs){
  *rhs.use++;
  if (this->use == 0) {
    delete this->ps;
    delete this->use;
  }
  this->ps = rhs.ps;
  this->i = i;
};

int main(int argc, char const *argv[]) {
  HasPtr boyao("boyao");
  boyao.getUse();
  HasPtr zixin(boyao);
  zixin.getUse();
  boyao.getUse();
  return 0;
}
