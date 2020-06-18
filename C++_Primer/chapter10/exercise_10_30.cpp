#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[]) {
  ifstream input("numbers");
  istream_iterator<int> in(input);
  istream_iterator<int> eof;
  //sort(in,eof);
  // ostream_iterator<int> out(cout);
  // copy(in,eof,out);
  // std::cout << endl;
  std::vector<int> v(in,eof);
  sort(v.begin(),v.end());
  // for(auto value: v)
  // {
  //   std::cout << value << '\n';
  // }
  unique_copy(v.begin(),v.end(),ostream_iterator<int>(cout," "));
  return 0;
}
