#include <iostream>
using namespace std;

template<typename T>
ostream& print(ostream &os, const T &t)
{
  return os << t ;
}

template<typename T, typename... Args>
ostream& print(ostream &os, const T &t, const Args... rest )
{
  os << t <<" ";
  return print(os,rest...);
}

int main(int argc, char const *argv[]) {
  print(cout, "name", 88, 99.11);
  return 0;
}
