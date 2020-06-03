#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {

  int value = 10;
  void *pVlaue = &value;
  int *pOut = static_cast<int*> (pVlaue);
  std::cout << *pOut << '\n';

  const int cValue =999;
  const int *pcValue = &cValue;
  int* cValueout = const_cast<int*> (pcValue);
  const char *cp;
  string scp = static_cast<string> (cp);



  return 0;
}
