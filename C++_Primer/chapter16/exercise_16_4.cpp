#include <iostream>
#include <vector>
#include <list>
using namespace std;

template<typename Iter, typename val>
Iter find(Iter beg, Iter end, const val& tofind)
{
  while (beg!=end && *beg!=tofind) {
    beg++;
  }
  return beg;
}

int main(int argc, char const *argv[]) {

  std::vector<int> v{1,2,3,4,5,6,7,8};
  auto result = find(v.begin(),v.end(),99);
  if (result == v.end()) {
    std::cout << "not found" << '\n';
  }else{
    std::cout << "found" << '\n';
  }

  list<string> ls{"zixin","axin","xiaokeai"};
  auto result2 = find(ls.begin(),ls.end(),"axin");
  if (result2 == ls.end()) {
    std::cout << "not found" << '\n';
  }else{
    std::cout << "found" << '\n';
  }

  return 0;
}
