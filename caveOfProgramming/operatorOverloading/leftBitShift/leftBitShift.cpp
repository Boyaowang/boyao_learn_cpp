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

  people& operator-(people& obj)
  {
    std::cout << "- is running" << '\n';
    age += obj.age;
    return *this;
  }

  void operator<<(people& obj)
  {
    age+=obj.age;
    std::cout << "run <<" << '\n';
  }
  // let's define our own copy constructor
  people(const people& obj)
  {
    name = obj.name;
    age= obj.age;
    std::cout << "copy constructor is running" << '\n';
  }

  friend ostream& operator<<(ostream& out, people person) //2 inputs are cout and boyao
  {
    out << person.name << " " << person.age << endl;
    return out;
  };

  virtual ~people (){};

  void printage()
  {
    std::cout << age << '\n';
  }
};

int main(int argc, char const *argv[]) {
  people boyao("boyao", 20);
  people jiechen("jiechen", 21);
  boyao+jiechen;
  boyao=boyao-jiechen;
  boyao.print();
  jiechen.print();
  boyao<<jiechen;
  boyao.print();
  std::cout << boyao << jiechen << '\n';
  return 0;
}
