#include <iostream>
#include <map>
#include <vector>
#include <algorithm> // for sort

using namespace std;

int main(int argc, char const *argv[]) {
  std::map<string, std::vector<int>> people;

  std::vector<int> scores;
  scores.push_back(89);
  scores.push_back(59);
  scores.push_back(90);

  sort(scores.begin(),scores.end());

  people["jiechen"] = scores;

  people["jianbiao"].push_back(70);
  people["jianbiao"].push_back(97);
  people["jianbiao"].push_back(78);
  people["jianbiao"].push_back(59);

  for (map<string, vector<int>>::iterator it = people.begin(); it != people.end(); it++) {
    std::cout << it->first << "'s marks are: " << '\n';
    for (std::vector<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
      std::cout << *it2 << '\n';
    }
  }
  // at function of map
  std::cout << "test .at()" << '\n';
  std::cout << people.at("jiechen")[0] << '\n';

  return 0;
}
