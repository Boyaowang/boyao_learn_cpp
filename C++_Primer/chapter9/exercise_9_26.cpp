#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main(int argc, char const *argv[]) {
  int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };

  std::vector<int> vi(begin(ia),end(ia));
  std::list<int> li(begin(ia),end(ia));

  std::vector<int>::iterator itv = vi.begin();
  std::list<int>::iterator itl = li.begin();

  while (itv != vi.end()) {
    if (*itv & 0x1) {
      itv = vi.erase(itv);
    }
    else ++itv;
  }

  for(auto value: vi)
  {
    std::cout << value << '\n';
  }
  return 0;
}
