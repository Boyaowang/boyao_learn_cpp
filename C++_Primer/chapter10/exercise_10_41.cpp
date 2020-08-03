#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[]) {
  std::vector<int> v{1,2,5,2,6,23,6,2,34,6,1};
  std::vector<int> v2(11);
  replace(v.begin(),v.end(),1,999);
  replace_copy(v.begin(),v.end(),v2.begin(),1,999);
  for(auto value : v)
  {
    std::cout << value << '\n';
  }
  for(auto value : v2)
  {
    std::cout << value << '\n';
  }
  return 0;
}
