#include <iostream>
#include <map>
#include <utility>
#include <fstream>
#include <set>

using namespace std;

int main(int argc, char const *argv[]) {
  ifstream myFriends("lots_of_friends");
  std::map<std::string, int> friends_map;

  string name;

  while (myFriends >> name ) {
    //auto it = friends_map.insert({name,1});
    pair<std::map<std::string, int>::iterator, bool> it = friends_map.insert({name,1});
    if (!it.second) {
      ++(it.first->second);
    }
  }

  for(auto obj : friends_map)
  {
    std::cout << obj.first << " " << obj.second<< '\n';
  }
  return 0;
}
