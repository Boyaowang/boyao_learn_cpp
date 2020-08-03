#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <utility>

using namespace std;

int main(int argc, char const *argv[]) {

   ifstream friends("friends");
   std::vector<pair<string,string>> v_friends;
   string f_name,l_name;
   while (friends >> f_name >> l_name) {
     v_friends.push_back({f_name,l_name});
   }

  for(auto value : v_friends)
  {
     std::cout << value.first << " " << value.second << '\n';
  }
  return 0;
}
