#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<class T>
void printYourVec(std::vector<T> v, ostream &os) {
  for_each(v.begin(),v.end(),[&os](const string &s){
    os << s << " ";
  });
}

int main(int argc, char const *argv[]) {
  std::vector<string> vs{"I","am","an","am","an","idiot","or","not","fuck!!"};
  printYourVec(vs,cout);
  return 0;
}
