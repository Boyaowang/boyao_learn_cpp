#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
  std::vector<int> v1(10,999);
  std::vector<int> v2(24,888);
  swap(v1,v2);
  for(auto value: v2)
  {
    std::cout << value << '\n';
  }
  return 0;
}
