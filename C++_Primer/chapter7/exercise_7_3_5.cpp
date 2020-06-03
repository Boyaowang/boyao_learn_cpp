#include <iostream>
using namespace std;

using Type = string;
class Exercise {
private:
  int val;

public:
  Exercise() = default;
  virtual ~Exercise (){};

  using Type = double;
  Type setVal(Type);
  Type initVal(){return 1.2;};
};

Exercise::Type Exercise::setVal(Type parm)
{
  ::Type s = "name";
  val = parm + initVal();
  std::cout << s << '\n';
  return val;
}

int main(int argc, char const *argv[]) {
  Exercise boyao;
  boyao.setVal(5);
  return 0;
}
