#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>

using namespace std;

int main(int argc, char const *argv[]) {
  //std::vector<int> v;
  istream_iterator<int> in(cin);
  istream_iterator<int> end_of_in; // can be end of file or io error
  // while (in!=end_of_in) {
  //   v.push_back(*in);
  //   in++;
  // }
  //std::cout << accumulate(in,end_of_in,0) << '\n';
  std::vector<int> v(in,end_of_in);
  ostream_iterator<int> out(cout," ");
  for(auto value:v)
  {
    //std::cout << value << '\n';
    out = value;
  }

  std::cout << endl;


  return 0;
}
