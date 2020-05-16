#include <iostream>
#include <vector>
using namespace std;

struct people {
  int age;
  string name;
}boyao={25,"boyao"},zixin={24,"zixin"},jiechen={25,"jiechen"};// initialized here

struct person {
  int age;
  string name;
}boyao2{25,"boyao"},zixin2{24,"zixin"},jiechen2{25,"jiechen"};// initialized here C++ 11 new func

int main(int argc, char const *argv[]) {

  //C++ 11
  int a(5);
  string text("name"); // or int a{5}; string text{"name"};
  int number[]{1,2,3};

  int* pArr= new int[5]{1,3,6,8,8};
  delete [] pArr;

  int* pa{&a};

  std::cout << a << '\n';
  std::cout << *pa << '\n';

  int* nullP{NULL};
  int* nullP2{nullptr};

  std::cout << nullP << '\n';
  std::cout << nullP2 << '\n';

  std::vector<int> v{1,2,3};

  for(auto value:v)
  {
    std::cout << value << '\n';
  }

  return 0;
}
