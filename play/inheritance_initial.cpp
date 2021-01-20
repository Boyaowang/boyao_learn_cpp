#include <iostream>
using namespace std;

template<typename T>
class parent {
private:
  string name;

public:
  parent (string name):name(name){};
  string returnName(){
    return this->name;
  };
  virtual ~parent (){};
};

class child :public parent<string>{
private:
  string parentName;

public:
  child (string name):parent(name),parentName(this->returnName()){};
  void printName() {
    std::cout << parentName << '\n';
  }
  virtual ~child (){};
};

int main(int argc, char const *argv[]) {
  child zixin("xiaomiaomiao");
  zixin.printName();
  return 0;
}
