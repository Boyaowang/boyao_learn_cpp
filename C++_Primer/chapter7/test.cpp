#include <iostream>
#include <vector>
using namespace std;

typedef int Iage;
int agePar =12;
class people {
private:
  int age =10;

  using Sname =string;
public:
  people (){};
  virtual ~people (){};

  Iage yourAge(){
    return age;
  }

  Sname yourName(){
    return name;
  }
  
  int results()
  {
    return age* ::agePar;
  }

private:
  string name;
  //typedef int Iage;

};

int main(int argc, char const *argv[]) {
  people boyao;
  std::cout << boyao.yourAge() << '\n';
  return 0;
}
