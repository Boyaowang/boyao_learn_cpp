#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main(int argc, char const *argv[]) {
  std::list<int> vi{1,2,4,5,6,7,8};
  auto begin = vi.begin();

  while (begin!=vi.end()) {
    begin++;
    begin = vi.insert(begin, 999); // insert before begin
    begin++;
  }

  for (auto value : vi) {
    std::cout << value << '\n';
  }

  return 0;
}
