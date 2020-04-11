#include <iostream>
using namespace std;

class test
{
private:
  int value;
public:
  test(){this->value=10;std::cout << "original object" << '\n';}
  test(test &other){std::cout << "new object" << '\n';}
void output() const {int value2=11; std::cout << value << '\n'; }
};

int main(int argc, char const *argv[]) {
  int value1=0;
  int value2=10;
   int const * pvalue=&value1;
  //*pvalue=value2;
  pvalue = &value2;
  std::cout << *pvalue << '\n';
  test bb;
  test cc=bb;
  bb.output();
  return 0;
}
