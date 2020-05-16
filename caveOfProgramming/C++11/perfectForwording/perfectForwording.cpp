#include <iostream>
using namespace std;

class test {
private:
  /* data */

public:
  test (){};
  virtual ~test (){};
};

void check(test& obj){
  std::cout << "lvalue" << '\n';
}

void check(test&& obj) {
  std::cout << "rvalue" << '\n';
}

template<class T>// imagine T is auto
void call(T&& obj) {
  //check(static_cast<T>(obj));
  check(forward<T>(obj));
}

int main(int argc, char const *argv[]) {

  test T;
  test& lt = T;
  test&& rt = test();
  auto&& art= T;
  auto&& art2=test();

  call(art);
  call(art2);
  call(test());
  return 0;
}
