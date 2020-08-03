#include <iostream>
using namespace std;

class test {
private:
  string name;
  int age;

public:
  friend ostream & operator << (ostream& os, test obj);
  test(string name = "zixin", int age = 24):name(name),age(age){};
  virtual ~test (){};
  operator int() const{return age;}
  explicit operator string() const{return name;}
};

ostream & operator << (ostream& os, test obj)
{
  os << obj.name;
  return os;
}

int main(int argc, char const *argv[]) {
  test zixin;
  std::cout << zixin << '\n';
  return 0;
}
