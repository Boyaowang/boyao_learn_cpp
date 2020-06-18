#include <iostream>
#include <fstream>
using namespace std;

string asddsd{"dfpg"};
bool ascender_or_descender(string word)
{
  return word.find_first_of(asddsd)==string::npos;
}

int main(int argc, char const *argv[]) {
  ifstream input("names");
  string word;
  string longestSize;
  while (input >> word) {
    if (ascender_or_descender(word)) {
      if (word.size() > longestSize.size()) {
        longestSize = word;
      }
    }
  }
  std::cout << longestSize << '\n';
  return 0;
}
