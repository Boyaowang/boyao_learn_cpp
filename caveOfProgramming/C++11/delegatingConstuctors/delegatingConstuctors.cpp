#include <iostream>
using namespace std;

class people {
private:

  int age;
  string name;

public:

  people():people("unknown", 0){};

  people(string name, int age):age(age), name(name){};

  virtual ~people (){};

  friend class peopleInfo;

};

class peopleInfo: public people {
private:
  double height;

public:
  peopleInfo(int age, string name, double height):people(name,age), height(height){};
  virtual ~peopleInfo (){};

  void printPeopleInfo() {
    std::cout << "name:" << name << " age:" << age << " height: " << height << '\n';
  }
};
int main(int argc, char const *argv[]) {

  peopleInfo boyao(25,"boyao",1.83);

  boyao.printPeopleInfo();
  return 0;
}
