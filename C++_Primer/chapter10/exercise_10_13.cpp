#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool length_3(string s)
{
  return s.size()<3;
}

int main(int argc, char const *argv[]) {

  std::vector<string> vs{"I","am","an","am","an","idiot","or","not","fuck!!"};
  auto it_3 = partition(vs.begin(),vs.end(),length_3);
  for (std::vector<string>::iterator it = it_3; it != vs.end(); it++) {
    std::cout << *it << '\n';
  }
  return 0;
}
