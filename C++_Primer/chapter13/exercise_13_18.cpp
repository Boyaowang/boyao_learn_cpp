#include <iostream>
using namespace std;

class Employee {
private:
  string name;
  static int unique_ID;
  int ID;
public:
  Employee() = default;
  Employee(string name):name(name){
    ID = unique_ID++;
  };
  virtual ~Employee (){};
};

int Employee::unique_ID = 1;

int main(int argc, char const *argv[]) {

  return 0;
}
