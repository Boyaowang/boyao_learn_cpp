#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;
using namespace std::placeholders;

bool isShorter(string::size_type sz, const string s)
{
  return s.size()<sz;
}

int main(int argc, char const *argv[]) {
  //std::vector<string> vs{"I","am","an","am","an","idiot","or","not","fuck!!"};
  // auto count = count_if(vs.begin(),vs.end(),bind(isShorter,3,_1));
  // std::cout << count << '\n';
  string boyao{"boyao"};
  std::vector<int> vi{1,2,3,4,5,6,7,8};

  auto it = find_if(vi.begin(),vi.end(),bind(isShorter,_1,boyao));

  std::cout << *it << '\n';
  return 0;
}
