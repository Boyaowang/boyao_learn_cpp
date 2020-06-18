#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
  std::vector<int> vi{1,2,6,2,4,5,6,7,8,1,5,76,7,8,9,9,5,45,45,35,24,2,1,12};
  std::cout << vi.capacity() << '\n';
  auto begin = vi.begin();
  while (begin!=vi.end()) {
    if (*begin & 0x1) {
      begin = vi.insert(begin,*begin);
      begin += 2;
    }
    begin++;
  }
  std::cout << vi.capacity() << '\n';
  for(auto value:vi)
  {
    std::cout << value << " ";
  }
  std::cout  << '\n';
  vi.shrink_to_fit();
  std::cout << vi.capacity() << '\n';
  return 0;
}
