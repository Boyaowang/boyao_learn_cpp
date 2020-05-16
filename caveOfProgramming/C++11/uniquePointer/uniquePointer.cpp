#include <iostream>
#include <functional>
#include <memory>
using namespace std;

class people {
private:
  int age;
  string name;

public:
  //people(){};
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

class people_ptr {
private:
  //people* pPeople; //= new people("boyao",10);
  unique_ptr<people> pPeople;

public:
  people_ptr ():pPeople(new people("jiechen",26)){};
  virtual ~people_ptr (){};
  void printName()
  {
    pPeople->callInfo();
  }
}jiechen;

int main(int argc, char const *argv[]) {
  unique_ptr<people> pPeople(new people("zixin",24));
  jiechen.printName();
  pPeople->callInfo();

  return 0;
}
