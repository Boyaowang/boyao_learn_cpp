#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[]) {
  list<string> words{"boyao","boyao","jiechen","zixin","jiechen","zixin"};
  words.sort();
  words.unique();
  for(auto value : words)
  {
    std::cout << value << '\n';
  }
  return 0;
}
