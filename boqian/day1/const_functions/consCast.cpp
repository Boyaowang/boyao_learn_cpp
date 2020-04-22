#include <iostream>
using namespace std;

class boyao
{
private:
  int a=0;
public:
  void increase() const
  {
    //a++;
    const_cast<boyao*>(this)->a=5;
    std::cout << a << '\n';
  };
};

int main(int argc, char const *argv[]) {
  boyao value;
  value.increase();
  return 0;
}
