#include <iostream>
using namespace std;

template<typename T, unsigned size>
constexpr unsigned arrSize(const T(&)[size])
{
  return size;
};

int main(int argc, char const *argv[]) {
  std::string s[] = {"axin","zixin","xiaokeai"};
  std::cout << arrSize(s) << '\n';
  return 0;
}
