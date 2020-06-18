#include <iostream>
#include "salesItems.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
using namespace std;

int main(int argc, char const *argv[]) {
  ifstream numbers("numbers");
  ofstream evenNum("even");
  ofstream oddNum("odd");
  istream_iterator<int> in(numbers),eof;
  std::vector<int> v_item{in,eof};
  ostream_iterator<int> odd(oddNum," "),even(evenNum," ");
  //sort(v_item.begin(),v_item.end(),compareISBN);
  for(auto value : v_item)
  {
    *(value%2 !=0 ? odd : even)++ = value;
  }
  return 0;
}
