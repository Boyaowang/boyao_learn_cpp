#include <iostream>
using namespace std;

class people {
private:
  int age{0};
  std::string name{"unknown"};

public:
  people()=default; // = delete you will delete this default constructor
  people(const people& obj) = default;
  people& operator=(const people& obj) = default;
  people (int age, string name):age(age), name(name){};
  virtual ~people (){};
  void print() {
    std::cout << name << " : " << age << '\n';
  }
}boyao{25,"boyao"};

int main(int argc, char const *argv[]) {
  boyao.print();
  people son = boyao;
  people Son;
  Son = boyao;
  son.print();
  Son.print();
  return 0;
}
