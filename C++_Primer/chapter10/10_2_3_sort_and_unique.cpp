#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void sorting_string(std::vector<string> &vs) {
  sort(vs.begin(),vs.end());
  for(auto value : vs)
  {
    std::cout << value << " ";
  }
  std::cout << '\n';
  auto it_end = unique(vs.begin(),vs.end());
  for(auto value : vs)
  {
    std::cout << value << " ";
  }
  std::cout << '\n';
  vs.erase(it_end,vs.end());
  for(auto value : vs)
  {
    std::cout << value << " ";
  }
  std::cout << '\n';
}

int main(int argc, char const *argv[]) {
  std::vector<string> vs{"I","am","an","am","an","idiot"};
  sorting_string(vs);
  return 0;
}
