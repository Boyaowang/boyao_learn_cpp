#include <iostream>
using namespace std;

class mutClass {
private:
  int age;
  mutable int foolAge;
  string name;

public:
  mutClass(int age, int foolAge, string name):age(age), name(name), foolAge(foolAge){};
  virtual ~mutClass (){};

  void changeYourFoolAge(int newage) const
  {
    foolAge = newage;
    //age = newage; is not allowed
  };
};

int main(int argc, char const *argv[]) {
  // mutable lambda
  int numOfCats = 10;
  [numOfCats]()mutable
  {
    numOfCats = 999;
    std::cout << numOfCats << '\n';
  }();
  return 0;
}
