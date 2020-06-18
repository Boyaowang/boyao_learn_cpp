#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[]) {
  list<int> l1{1,2,3,4};
  list<int> l2,l3,l4;
  copy(l1.begin(),l1.end(),front_inserter(l2));
  copy(l1.begin(),l1.end(),back_inserter(l4));
  copy(l1.begin(),l1.end(),inserter(l3,l3.begin()));
  for(auto value : l2)
  {
    std::cout << value << '\n';
  }
  for(auto value : l3)
  {
    std::cout << value << '\n';
  }
  for(auto value : l4)
  {
    std::cout << value << '\n';
  }
  return 0;
}
