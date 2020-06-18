#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
  std::vector<string> vs;
  std::list<const char*> lc(10,"f");
  vs.assign(lc.begin(),lc.end());
  for(std::vector<string>::iterator it = vs.begin();it!= vs.end();it++)
  {
    std::cout << *it << '\n';
  }
  std::cout << vs.max_size() << '\n';
  std::cout << lc.max_size() << '\n';
  return 0;
}
