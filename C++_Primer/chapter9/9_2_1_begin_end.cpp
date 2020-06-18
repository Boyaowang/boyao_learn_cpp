#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
  std::vector<int> vi{1,2,4,5,7};
  std::vector<int>::iterator it= vi.begin();
  while (it!=vi.end()) {
    *it = 999;
    it++;
  }
  for(auto value: vi)
  {
    std::cout << value << '\n';
  }
  return 0;
}
