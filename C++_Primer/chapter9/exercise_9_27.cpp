#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
using namespace std;

int main(int argc, char const *argv[]) {

  int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };

  forward_list<int> fli(begin(ia),end(ia));
  auto prev = fli.before_begin();
  auto curr = fli.begin();

  while (curr != fli.end()) {
    if (*curr & 0x1) {
      curr = fli.erase_after(prev);
    }
    else {
      prev =curr;
      // or ++prev;
      ++curr;

    }
  }

  for(auto value: fli)
  {
    std::cout << value << '\n';
  }
  return 0;
}
