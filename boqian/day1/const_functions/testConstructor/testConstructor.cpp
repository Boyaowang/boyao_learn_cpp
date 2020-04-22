#include <iostream>
using namespace std;

class boyao
{
public:
  boyao(){std::cout << "/* message */" << '\n';};
};

class boyao2
{
  boyao object;
};

int main(int argc, char const *argv[]) {
  boyao2 obj;
  return 0;
}
