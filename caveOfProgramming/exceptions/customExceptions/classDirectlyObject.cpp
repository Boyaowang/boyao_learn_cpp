#include <iostream>
using namespace std;

class longName {
private:
  /* data */

public:
  longName (){std::cout << "/* message */" << '\n';};
  virtual ~longName (){};
  void haha() {
    std::cout << "haha" << '\n';
  }
}(name),haha;

int main(int argc, char const *argv[]) {
  name.haha();
  return 0;
}
