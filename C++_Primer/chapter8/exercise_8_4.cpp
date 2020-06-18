#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void read(std::vector<string> &vs) {
  ifstream input("books");
  if (input) {
    string s;
    while (getline(input,s)) {
      vs.push_back(s);
    }
  }
}

void read2(std::vector<string> &vs) {
  ifstream input("books");
  if (input) {
    string s;
    while (input>>s) {
      vs.push_back(s);
    }
  }
}

int main(int argc, char const *argv[]) {


  std::vector<string> vs;
  read(vs);
  for(auto value : vs)
  {
    std::cout << value << '\n';
  }

  std::vector<string> vs2;
  read2(vs2);
  for(auto value : vs2)
  {
    std::cout << value << '\n';
  }

  return 0;
}
