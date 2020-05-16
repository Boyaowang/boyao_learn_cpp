#include <iostream>
using namespace std;

class test {
private:
  /* data */

public:
  test (){};
  virtual ~test (){};
};

test getTest()
{
  return test();
}

void check(test& obj)
{
  std::cout << "Lvalue Func" << '\n';
}

void check(int obj)
{
  std::cout << "Lvalue Func" << '\n';
}

void check(test&& obj)
{
  std::cout << "Rvalue Func" << '\n';
}

int main(int argc, char const *argv[]) {
  int value = 999; // value is a Lvalue 999 is a Rvalue
  int* pvalue = &value;
//  int* pvalue = &999; // doesn't work because 999 is Rvalue
  test boyao;
  //test &&boyao = getTest();
  test &&boyao2 = test();

  check(boyao);
  check(boyao2);

  check(getTest());

  


  return 0;
}
