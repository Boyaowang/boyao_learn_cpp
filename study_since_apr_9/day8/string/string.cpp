#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[]) {
  string x;
  getline(cin, x);
  std::cout << x << '\n';
  std::cout << sizeof(x)/sizeof(string) << '\n';
  // string substr first value: strating position second value: how many to show
  std::cout << "substr function "<< x.substr(1,5) << '\n';
  //string initialize and assign
  string y("name");
  int a(5);
  std::cout << y << a << '\n';
  string z;
  z.assign(y);
  std::cout << z << '\n';
  // string.at
  string wby[2]={"name", "age"};
  std::cout << wby[0].at(0) << '\n';
  // string.length
  for (int i = 0; i < y.length(); i++) {
  std::cout << y.at(i) << '\n';
  }
  // string find
  string forFind("I am your father am I?");

  std::cout << forFind.find("am") << '\n';
  std::cout << forFind.rfind("am") << '\n';
  //string replace
  string forReplace=forFind;
  forReplace.replace(10,6,"mom");
  std::cout << forReplace << '\n';

  //string insert
  string forInsert = forFind;
  forInsert.insert(10, "lovely ");
  std::cout << forInsert << '\n';
  // string erase

  forFind.erase(5);
  std::cout << forFind << '\n';
  return 0;
}
