#include <iostream>
#include <sstream>
using namespace std;

int main()
{
  int age = 31;
  string name="Bob";
  stringstream ss;
  ss<< "Name is: ";
  ss<< name;
  ss<< "; Age is: ";
  ss<< age;
  std::cout << ss.str() << '\n';
}
