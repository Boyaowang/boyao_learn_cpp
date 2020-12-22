#include <iostream>
#include <memory>
using namespace std;

#define boyao(type1,argName)\
typedef shared_ptr<type1> argName##argList

#define boyao2(type1,argName)\
typedef shared_ptr<type1> (*argName##hahaha)

typedef void (*argName_test)(const int& a); // int (*)(const int&)

#define AXINXIN(function_type, Typename, para_List)\
typedef function_type (*Typename##function_type)para_List

void print(const int& a)
{
  std::cout << a << '\n';
};

int main(int argc, char const *argv[]) {
  // boyao(int,zixin);
  // zixinargList xiaoboyao;
  // xiaoboyao = make_shared<int>(42);
  // boyao2(int,zixin2);
  // zixin2hahaha a = &xiaoboyao;
  // std::cout << *a << '\n';
  // argName_test testprint = print;
  // testprint(555);
  AXINXIN(void, printxiaoboyao, (const int&));
  printxiaoboyaovoid xiaoboyao = print;
  xiaoboyao(999);

  return 0;
}
