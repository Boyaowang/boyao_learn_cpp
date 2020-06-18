#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
  std::vector<int> vi;
  auto it = back_inserter(vi);
  fill_n(it,10,0);
  for(auto value: vi)
  {
    std::cout << value << '\n';
  }
  return 0;
}
