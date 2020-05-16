#include <iostream>
#include <functional>
using namespace std;

class people {
private:
  int age;
  string name;

public:
  people(string name, int age):age(age), name(name){

  };
  virtual ~people (){};
  // a lambdaFunction

  void printInfo()
  {
    //void(*printInfo)()=[this](){};
    auto printInfo = [this](){
    };
    std::cout << typeid(printInfo).name() << '\n';
    printInfo();
  }

  //void(*callInfo)() = [](){std::cout << "" << '\n';};
  //people<void()> callInfo = [](){std::cout << "" << '\n';}

  function<void()> callInfo =  [this](){std::cout << age << " : "<< name << '\n';};

}boyao("boyao", 25);




int main(int argc, char const *argv[]) {
  boyao.printInfo();
  boyao.callInfo();
  return 0;
}
