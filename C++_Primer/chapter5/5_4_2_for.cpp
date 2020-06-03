#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
  std::vector<int> v ={1,2,3,4,5};
  auto beg = v.begin();

  std::cout << *beg << '\n';

  for (; beg != v.end(); beg++){
    std::cout << *beg << '\n';
  }

  std::cout << "This means beg has been changed by the for loop "<<*(beg-1) << '\n';
  return 0;
}
