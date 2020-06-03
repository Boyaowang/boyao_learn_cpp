#include <iostream>
using namespace std;

void printErr(initializer_list<int> li) {
  int cnt=0;
  for ( auto elem: li) {
    std::cout << elem << '\n';
    cnt+=elem;
  }
  std::cout << cnt << '\n';
}

int main(int argc, char const *argv[]) {
  initializer_list<int> li = {1,2,3,4,5};
  printErr(li);
  printErr({1,3,5});
  return 0;
}
