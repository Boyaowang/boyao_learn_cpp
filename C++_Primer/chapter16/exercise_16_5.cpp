#include <iostream>
using namespace std;

template<typename arrType>
void print(const arrType& arr) {
  for(auto val:arr)
  {
    std::cout << val << " ";
  }
  std::cout << '\n';
}

int main(int argc, char const *argv[]) {
  int i[] = {1,2,3,4,5};
  print(i);
  std::string s[] = {"axin","zixin","xiaokeai"};
  print(s);
  return 0;
}
