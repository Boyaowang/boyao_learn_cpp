#include <iostream>
#include <cstring>
using namespace std;

template<int a, int b>
int compare(const char (&c1)[a], const char (&c2)[b])
{
  std::cout << a << " " << b << '\n';
  return strcmp(c1,c2);
}

template<typename T>
int compare(const T&a, const T&b)
{
  if(less<T> ()(a,b)) return 1;
  if(less<T>()(b,a)) return 0;
  return -1;
}

int main(int argc, char const *argv[]) {
  compare<string>("hi","mom");
  less<int> lessthan;
  std::cout << plus<int> ()(1,3) << '\n';
  std::cout << compare(1,2) << '\n';
  return 0;
}
