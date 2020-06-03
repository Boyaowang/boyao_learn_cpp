#include <iostream>
using namespace std;

class test {
private:
  int ivalue =0;
  string svalue ="unknown";

public:
  test() = default;
  test (string s):svalue(s){};
  virtual ~test (){};

  test& callTest(const test& rhs)
  {
    this->svalue = rhs.svalue;
    return *this;
  }

  void printsvalue()
  {
    std::cout << svalue << '\n';
  }
};

string zixinName(){
	return "zixin";
}
int main(int argc, char const *argv[]) {
  test boyao;
  test jiechen("jiechen");
  string zixin ="zixin";
  boyao.callTest(jiechen.callTest(boyao.callTest(zixin)));
  boyao.printsvalue();
  const test& obj = zixinName();
  return 0;
}
