#include <iostream>
#include <vector>
using namespace std;

class Test {
private:

public:
  Test(){
    std::cout << "constructor" << '\n';
  };

  Test(const Test& obj){
    std::cout << "copy constructor" << '\n';
  };

  Test operator=(const Test& obj){
    std::cout << "assign" << '\n';
    *this = obj;
    return *this;
  }

  virtual ~Test(){
    std::cout << "destructor" << '\n';
  };
  friend ostream &operator<<(ostream& out, const Test obj);
};

ostream &operator<<(ostream& out, const Test obj){
  out << "something";
  return out;
}

Test getTest()
{
  return Test();
}


int main(int argc, char const *argv[]) {

  Test boyao = getTest();

  std::cout << boyao << '\n';

  std::vector<Test> vTest;
  vTest.push_back(Test());
  vTest.push_back(Test());
  vTest.push_back(Test());


  return 0;
}
