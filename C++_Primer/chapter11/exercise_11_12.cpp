#include <iostream>
#include <utility>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {
  std::vector<pair<string,int>> v;
  ifstream friends("friends_age");

  string name;
  int age;

  while (friends >> name >> age ) {
    v.push_back({name,age});
  }

  for(auto pairs : v)
  {
    std::cout << pairs.first << " " << pairs.second << '\n';
  }
  return 0;
}
