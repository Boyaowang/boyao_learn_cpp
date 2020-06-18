#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>

using namespace std;

int main(int argc, char const *argv[]) {

  ifstream in("names");

  istream_iterator<string> string_in(in);
  istream_iterator<string> eof;

  std::vector<string> vs(string_in,eof);

  for(auto value: vs)
  {
    std::cout << value << '\n';
  }

  return 0;
}
