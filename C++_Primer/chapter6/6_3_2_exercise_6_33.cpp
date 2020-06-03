//#define NDEBUG
#include <iostream>
#include <vector>
using namespace std;

void printVec(std::vector<int> &v, std::vector<int>::iterator it) {// remember to add a reference here
  if (it!=v.end()) {
    //#ifndef NDEBUG
    cerr << *(it++) << '\n';
    printVec(v,it);
    //#endif
  }
  return;
}
int main(int argc, char const *argv[]) {
  std::vector<int> v{1,2,3,4,5};
  printVec(v,v.begin());
  return 0;
}
