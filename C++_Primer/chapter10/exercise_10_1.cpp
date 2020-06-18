#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[]) {

  std::vector<int> v{1,24,1,467,78,2,25,1,356,1,63};
  std::cout << count(v.begin(),v.end(),1) << '\n';

  list<string> ls{"boyao","jiechen","zixin"};
  std::cout << count(ls.begin(),ls.end(),"zixin") << '\n';
  return 0;
}
