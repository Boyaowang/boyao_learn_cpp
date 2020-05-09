#include <iostream>
#include <vector>
using namespace std;

void helloworld() {
  std::cout << "helloworld" << '\n';
}

void printValue(int value){
  std::cout << value << '\n';
}

void forPrint(std::vector<int> v, void(*func)(int))
{
  for(int value:v)
  {
    func(value);
  }
}

int main(int argc, char const *argv[]) {
  void(*phelloworld)() = helloworld;
  phelloworld();

  void(*pprintValue)(int) = printValue;
  pprintValue(5);

  std::vector<int> v = {1,3,7,8,3};

  forPrint(v,pprintValue);

  // Or

  forPrint(v,[](int value){std::cout << value << '\n';}); // called lambda?


  return 0;
}
