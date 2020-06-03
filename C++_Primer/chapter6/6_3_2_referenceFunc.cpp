#include <iostream>
using namespace std;

  string &shortString( string &s1,  string &s2){
  string &result = (s1.size()<= s2.size()) ? s1 : s2;
  //std::cout << "address of result and s " << &result<<" " << &s1 << " " << &s2 << '\n';
  return result;
}

int main(int argc, char const *argv[]) {
  string s1 = "boyao";
  string s2 = "jiechen";
  shortString(s1,s2) = "you are short";
  std::cout << shortString(s1,s2).size() << '\n';
  std::cout << s1 << '\n';
  return 0;
}
