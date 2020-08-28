#include <iostream>
using namespace std;

template <typename T>
typename remove_reference<T>::type && myMove(T && t)
{
  return static_cast<typename remove_reference<T>::type &&>(t);
}

string && print(string& a)
{
  return static_cast<string&&>(a);
}



int main(int argc, char const *argv[]) {
  string a = "string";
  string b = myMove(a);
  std::cout << a << " and b is " << b << '\n';
  int ai =10;
  int bi = myMove(ai);
  std::cout << ai << '\n';
  string a2 = "zixin";
  string b2 = print(a);
  std::cout << a << '\n';
  return 0;
}
