#include <iostream>

using namespace std;

class people {
private:
  int age;
  string name;

public:
  people(){};
  people(string name, int age):name(name),age(age){};

  void print() {
    std::cout << name <<" " << age <<'\n';
  }

  const people& operator=(const people& obj)
  {
    name = obj.name;
    age= obj.age;
    std::cout << "operator overloading is running" << '\n';
    return *this;
  }

  void operator+(people& obj)
  {
    age+=obj.age;
    std::cout << "run +" << '\n';
  }
  // let's define our own copy constructor
  people(const people& obj)
  {
    name = obj.name;
    age= obj.age;
    std::cout << "copy constructor is running" << '\n';
  }

  virtual ~people (){};

  void printage()
  {
    std::cout << age << '\n';
  }
};
int main(int argc, char const *argv[]) {
  people jiechen("jiechen",10);
  jiechen.printage();
  people jiechen2;
  jiechen2=jiechen;
  //But this is a copy constructor
  people jiechen3 = jiechen;

  jiechen.printage();
  jiechen2.printage();
  jiechen3.printage();

  people boyao("boyao", 29);
  boyao+jiechen;
  boyao.printage();
  return 0;
}
