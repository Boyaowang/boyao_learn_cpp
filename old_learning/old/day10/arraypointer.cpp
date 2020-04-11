#include <iostream>
using namespace std;

int main() {
  string furnature[3][3]={
    {"chair","sofa"},
    {"TV","phone"},
    {"kitchen","fan"}
};
string *pfurnature= furnature[0];
//pfurnature++;
cout << "array is actually a address, furnature has an address of "
<< pfurnature << " "<<furnature <<endl;

  return 0;
}
