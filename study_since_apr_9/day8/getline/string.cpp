#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[]) {
  string x;
  getline(cin, x);
  std::cout << x << '\n';
  std::cout << sizeof(x)/sizeof(string) << '\n';

  std::cout << "substring"<< x.substring(5,2) << '\n';

  string y("name");
  int a(5);
  std::cout << y << a << '\n';
  string z;
  z.assign(y);
  std::cout << z << '\n';

  string wby[2]={"name", "age"};
  std::cout << wby[0].at(0) << '\n';

  for (int i = 0; i < y.length(); i++) {
  std::cout << y.at(i) << '\n';
  }

  return 0;
}
