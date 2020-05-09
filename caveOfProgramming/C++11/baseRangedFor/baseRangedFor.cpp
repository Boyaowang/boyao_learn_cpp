#include <iostream>
#include <vector>
using namespace std;

namespace boyao{
  class jiechen{
  public:
    jiechen(){std::cout << "/* message */" << '\n';};
  };
}
int main(int argc, char const *argv[]) {
  std::vector<string> nameList;
  nameList.push_back("boyao");
    nameList.push_back("zixin");
      nameList.push_back("jiechen");
        nameList.push_back("zhongwei");

  for (auto name:nameList) {
    std::cout << name << '\n';
  };

  string name = "hello";
  for (auto Name:name) {
    std::cout << Name << '\n';
  };

  string arr[2]= {"hi","hello"};
  for (auto Name:arr) {
    std::cout << Name << '\n';
  };

  return 0;
}
