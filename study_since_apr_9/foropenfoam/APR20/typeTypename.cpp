#include <iostream>
using namespace std;

class nameInfo
{
public:
  string name="unknown";
public:
  nameInfo() = default;
  nameInfo(string name):name(name)
  {std::cout << "yourname initialized" << '\n';};

  void printName()
  {
    std::cout << name << '\n';
  }
  struct nickName
  {
    void printname()
    {
      std::cout << "/* message */" << '\n';
    }
  };
};

template<class name>
class company:public name
{
public:
  typedef typename name::nickName nickName;
  nickName boyao;
  void printPrintName() {
    boyao.printname();
  }

  nameInfo jiechen;
  void printPrintName2() {
    jiechen.printName();
  }

};

typedef company<nameInfo> companyNameInfo;

int main(int argc, char const *argv[]) {
  companyNameInfo boyao;
  boyao.printPrintName();
  boyao.printPrintName2();
  return 0;
}
