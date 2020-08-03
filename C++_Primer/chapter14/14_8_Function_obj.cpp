#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct printStr {
  ostream &os;
  char sep;
  printStr(ostream &os = cout, char sep = ' '):os(os),sep(sep){}
  void operator()(const string& s)const{os << s << sep;}
};
int main(int argc, char const *argv[]) {
  printStr zixin;
  zixin.operator()("zixin");
  zixin("xiaokeai");
  std::vector<string> vs{"zixin","xiaokeai","xiaotiancai"};
  for_each(vs.begin(),vs.end(),printStr(cout,'\n'));
  return 0;
}
