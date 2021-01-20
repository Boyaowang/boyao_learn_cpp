#include <iostream>
#include <tuple>
#include <list>
#include <fstream>
#include <memory>
using namespace std;

int main(int argc, char const *argv[]) {
  tuple<int, string, int> tp1(1,"name", 2);
  list<tuple<string, int>> nameAge;
  ifstream in("tuppleList");
  string a;
  int b;
  while (in >> a >> b) {
    nameAge.push_back(make_tuple(a,b));
  }
  for (auto it = nameAge.begin(); it!= nameAge.end(); it++) {
    std::cout << get<0>(*it) << '\n';
  }

  shared_ptr<int> value(new int(5));
  const int& valueR = *value;
  return 0;
}
