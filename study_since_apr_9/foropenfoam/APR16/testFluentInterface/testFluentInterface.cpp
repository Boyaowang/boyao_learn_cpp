#include <iostream>
using namespace std;

class cloud
{
public:
  int a;
  cloud(int a):a(a){};
  cloud add(int a)
  {
    this->a+=a;
  };
  cloud show1()
  {
    std::cout << "/* message1 */" << '\n';
  };
  cloud& show2()
  {
    std::cout << "/* message2 */" << '\n';
  };
};

int main(int argc, char const *argv[]) {
  cloud boyao(0);
  boyao.show1().show2().add(5);
  return 0;
}
