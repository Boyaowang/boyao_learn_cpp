#include <iostream>
using namespace std;

void process_input(istream& is) {
  string s;
  is >> s;
  std::cout << "string s is  "<<s << '\n';
}
int main(int argc, char const *argv[]) {
  // int s;
  // std::cin >> s;
  // auto old_state = cin.rdstate();
  // std::cout << old_state << '\n';
  // std::cout << "s is = "<< s << '\n';
  // cin.clear();
  // std::cout << cin.rdstate() << '\n';
  // process_input(cin);
  // cin.setstate(old_state);
  std::cout << cin.failbit << " "<< cin.badbit << " "<<cin.eofbit << " " << cin.goodbit<< '\n';
  return 0;
}
