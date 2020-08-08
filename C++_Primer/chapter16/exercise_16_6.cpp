#include <iostream>
using namespace std;

template<typename T, int size>
T* arrBeg(T(&arr)[size])
{
  return arr;
}

template<typename T, int size>
T* arrEnd(T(&arr)[size])
{
  return (arr+size);
}

int main(int argc, char const *argv[]) {
  std::string s[] = {"axin","zixin","xiaokeai"};
  std::cout << *arrBeg(s) << '\n';
  for (auto it = arrBeg(s); it != arrEnd(s); it++) {
    std::cout << *it << '\n';
  }
  return 0;
}
