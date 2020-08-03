#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {
  std::map<string, int> friends_age;
  std::map<string, int>::key_type boyao = "boyao";
  ifstream friends("friends_age");
  string name;
  int age;

  while (friends >> name >> age) {
    friends_age[name]=age;
  }


  std::cout << friends_age[boyao] << '\n';

  for (std::map<string, int>::const_iterator map_it = friends_age.begin(); map_it != friends_age.end(); map_it++) {
    std::cout << map_it->first <<" " << (*map_it).second<< '\n';
  }


  return 0;
}
