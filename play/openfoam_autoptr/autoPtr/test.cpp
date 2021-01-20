#include <iostream>
using namespace std;
#include "autoPtr.H"
using namespace Foam;

int main(int argc, char const *argv[]) {
  autoPtr<int> testAuto(new int(10));
  int* valp(new int(11));
//  const int& testAutoR = testAuto;
  int& myOp = testAuto;
  int* mypointer = testAuto;
  std::cout << mypointer << '\n';
  return 0;
}
