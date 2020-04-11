#include <iostream>
using namespace std;

void inname();// declaration
void outname(const char* name) {
  std::cout << name << '\n';
}
class statictest{
public:

void loop()
{
  static int a=2;
  int b=1;
  a++;
  std::cout << a << " with address " << &a<<'\n';
  std::cout << b << " with address "<< &b<<'\n';
}
};
int main()
{
    //char name[8];
    //cin.get(name, 8);
    outname("hello world!");
    statictest testa;
    for (int i = 0; i < 5; i++) {
      testa.loop();
    }
    std::cout << "/* message */" << '\n';
    return 0;
}
