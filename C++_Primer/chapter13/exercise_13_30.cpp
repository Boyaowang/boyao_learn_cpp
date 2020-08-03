#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class HasPtr {
private:
  string *ps;
  int i;
public:
  HasPtr(const string s):ps(new string(s)),i(0){};
  HasPtr(const HasPtr &hp):ps(new string(*hp.ps)),i(hp.i){};
  HasPtr &operator=(const HasPtr &rhs){
    auto new_ps=new string(*rhs.ps);
    delete ps;
    ps = new_ps;
    i = rhs.i;
    return *this;
  };
  virtual ~HasPtr (){delete ps;};
  // the swap function
  friend void HasPtr_swap(HasPtr &lhs, HasPtr &rhs);
  friend bool operator < (const HasPtr &lhs, const HasPtr &rhs);
  void print() {
    std::cout << *ps << '\n';
  }
};

void HasPtr_swap(HasPtr &lhs, HasPtr &rhs)
{
  swap(lhs.ps,rhs.ps);
  swap(lhs.i,rhs.i);
  std::cout << "call swap" << '\n';
}

bool operator < (const HasPtr &lhs, const HasPtr &rhs)
{
  return *lhs.ps < *rhs.ps;
}

int main(int argc, char const *argv[]) {
  HasPtr boyao("boyao");
  HasPtr zixin("zixin");
  // HasPtr_swap(boyao,zixin);
  // zixin.print();
  // boyao.print();

  std::vector<HasPtr> myLove;
  HasPtr strawberry("strawberry");
  HasPtr litteGenius("litteGenius");
  myLove.push_back(zixin);
  myLove.push_back(strawberry);
  myLove.push_back(litteGenius);

  sort(myLove.begin(),myLove.end());
  for(auto value:myLove)
  {
    value.print();
  }
  return 0;
}
