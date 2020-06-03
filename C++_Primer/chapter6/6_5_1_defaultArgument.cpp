#include <iostream>
#include <cassert>
using namespace std;

inline void defaultFunc(int age , string name ="unknown" , char hehe = 'h'){
  std::cout << "your name is "<< name<< "\nyour age is "<< age << hehe<< '\n';
  std::cout << __func__ << '\n';
  std::cout << __FILE__ << '\n';
  std::cout << __LINE__ << '\n';
  std::cout << __DATE__<<" "<<__TIME__ << '\n';
};

// void defaultFunc(int = 0, string = "unknown"){
//
// };
//
// typedef string::size_type sz;
//
// sz wd = 80;
// char def = ' ';
// sz ht();
// string screen(sz = 10, sz = wd, char = ' ');


int main(int argc, char const *argv[]) {
  //defaultFunc();
  defaultFunc(25,"boyao");
  defaultFunc(20);

  int a , b;
  std::cin >> a >> b;
  assert(a>b);
  assert(a<b);


  return 0;

}
