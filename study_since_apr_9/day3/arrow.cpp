#include <iostream>
using namespace std;

class boyao
{
public:
  boyao(){};
  void printsomething(){
    std::cout << "/* message */" << '\n';
  }
};


int main(int argc, char const *argv[]) {
  boyao a;
  boyao* b= &a;
  a.printsomething();
  b->printsomething();
  return 0;
}
