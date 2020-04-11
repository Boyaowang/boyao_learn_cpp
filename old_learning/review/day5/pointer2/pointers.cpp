#include <iostream>
using namespace std;

void manip(int* value)
{
  *value=*value+1995;
};

int main(int argc, char const *argv[]) {
  int nvalue=5;
  int* pnvalue= &nvalue;
  std::cout << "The address of nvalue is " << pnvalue << '\n';
  std::cout << "The value of nvalue is "<< nvalue << '\n';
  manip(&nvalue);
  std::cout << "The manipulate nvalue is "<< nvalue << '\n';
  return 0;
}
