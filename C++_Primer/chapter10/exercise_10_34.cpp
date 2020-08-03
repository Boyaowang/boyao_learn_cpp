#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[]) {
  std::vector<string> vs{"boyao","jiechen","zixin"};
  for(auto it = vs.rbegin();it!= vs.rend();it++)
  {
    std::cout << *it << '\n';
  }
  for(auto it = vs.end()-1;it!= vs.begin()-1;it--)
  {
    std::cout << *it << '\n';
  }

  std::list<int> lst = { 1, 2, 3, 4, 0, 5, 6 };
  auto zero_elem = find(lst.rbegin(),lst.rend(),0);
  std::cout << *zero_elem << '\n';

  std::list<int> lst2(5);
  std::vector<int> vi{1,2,3,4,5,6,7,8,9,0};
  copy(vi.rbegin()+3,vi.rbegin()+8,lst2.begin());
  for(auto value : lst2)
  {
    std::cout << value << '\n';
  }
  return 0;
}
