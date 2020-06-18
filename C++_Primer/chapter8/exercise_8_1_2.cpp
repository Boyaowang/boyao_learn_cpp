#include <iostream>
using namespace std;

istream& callIstream(istream& is) {
  int value;
  while (is>>value) {
      std::cout << value << '\n';
  }
  is.clear();
  std::cout << is.rdstate() << '\n';
  return is;
}

int main(int argc, char const *argv[]) {
  int a;
  istream& is = callIstream(cin);
  callIstream(cin)>> a;
  std::cout << is.rdstate() << " " <<a << '\n';
  return 0;
}
