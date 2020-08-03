#include <iostream>
#include <map>
#include <fstream>
#include <set>

using namespace std;

int main(int argc, char const *argv[]) {
  set<string> exclude{"example"};
  ifstream friends("friends");
  std::map<string, int> map_friends;
  string name;

  while (friends >> name) {
    if (exclude.find(name) == exclude.end()) {
      auto it = map_friends.insert({name,1});
      //++map_friends[name];
      if (!it.second) {
        ++it.first->second;
      }
    }
  }

  for(auto value : map_friends)
  {
    std::cout << value.first << " appears "<< value.second << '\n';
  }

  for (pair<std::map<string, int>::iterator, std::map<string, int>::iterator> it = map_friends.equal_range("boyao"); it.first!=it.second; ++it.first) {
    std::cout << it.first->second << '\n';
  }

  return 0;
}
