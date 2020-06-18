#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[]) {
  std::vector<string> vs{"I","am","an","am","an","idiot","or","not","fuck!!"};
  sort(vs.begin(),vs.end());
  list<string> ls;
  unique_copy(vs.begin(),vs.end(),inserter(ls,ls.begin()));
  for(auto value:ls)
  {
    std::cout << value << '\n';
  }
  return 0;
}
