#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {
  std::map<string, std::vector<string>> map_family;
  ifstream friends("friends");
  string f_name,l_name;
  while (friends >> f_name >> l_name) {
    map_family[l_name].push_back(f_name);
  }

  for(auto value : map_family)
  {
    for(auto names : value.second)
    {
      std::cout << names << '\n';
    }
  }
  return 0;
}
