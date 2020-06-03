#include <iostream>
#include <vector>
using namespace std;

int add(int a, int b)
{
  return a+b;
}

int subtract(int a, int b)
{
  return a-b;
}

typedef int(*padd)(int,int);

int main(int argc, char const *argv[]) {

  std::vector<int(*)(int,int)> v;

  v.push_back(add);
  v.push_back(subtract);
  std::cout << v[0](1,9) << '\n';
  std::cout << v[1](1,9) << '\n';

  return 0;
}
