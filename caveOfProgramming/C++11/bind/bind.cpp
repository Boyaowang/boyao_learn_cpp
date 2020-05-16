#include <iostream>
#include <functional>

using namespace std;
using namespace placeholders;

int add(int a, int b)
{
  return a+b;
}

void names(string a, string b, string c)
{
cout << a << " " << b << " "<< c << endl;
}

int run(function<int(int, int)> func ,int a, int b) {
  func(a,b);
}

int main(int argc, char const *argv[]) {
  auto calculateAdd = bind(add,1,2);
  auto calculateAdd2 = bind(add,_1,_2);
  std::cout << calculateAdd() << '\n';
  std::cout << calculateAdd2(20,50) << '\n';

  auto nameList = bind(names, _2, _1, _3);
  nameList("boyao","jiechen","zixin");

  std::cout << run(add, 1, 4) << '\n';
  std::cout << run(calculateAdd2, 20, 1) << '\n';
  return 0;
}
