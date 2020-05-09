#include <iostream>
using namespace std;

struct test{
  virtual bool operator()(string name) = 0;
};

struct matchTest : public test {
  bool operator+(string name)
  {
    return name=="jiechen";
  }

  bool operator()(string name) //here the bracket is just a operator
  {
    return name=="jiechen";
  }

};

void check(string name, test& obj)
{
  if (obj(name)) {
    std::cout << "name match!" << '\n';
  } else {
    std::cout << "name is wrong" << '\n';
  }
}

int main(int argc, char const *argv[]) {
  matchTest boyao;
  std::cout << boyao+"jiechen" << '\n';
  std::cout << boyao("jiechen") << '\n';

  std::cout << "***************************" << '\n';

  check("jiechen", boyao);
  return 0;
}
