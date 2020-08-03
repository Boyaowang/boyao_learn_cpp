#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class foo {
private:
  std::vector<string> data;

public:
  foo(const initializer_list<string>& il){
    for(auto value:il)
    {
      data.push_back(value);
    }
  };

  void printVec(/* arguments */) {
    for(auto value:data)
    {
      std::cout << value << '\n';
    }
  }
  std::vector<string> retVec(){
    return data;
  };
  virtual ~foo (){};
  foo sorted() &&;
  foo sorted() const &;
};

foo foo::sorted() &&
{
  sort(data.begin(),data.end());
  std::cout << "call &&" << '\n';
};

foo foo::sorted() const &
{
  foo cpData(*this);
  sort(cpData.data.begin(),cpData.data.end());
  std::cout << "call &" << '\n';
  return cpData;
}

int main(int argc, char const *argv[]) {
  foo zixin{"zixin","little_genius"};
  zixin.sorted();
  zixin.printVec();

  return 0;
}
