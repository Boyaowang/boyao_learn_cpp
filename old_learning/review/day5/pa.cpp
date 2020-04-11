#include <iostream>
using namespace std;

int main() {
  string arr[]={"one","two","three"};
  string *parr=arr;
  std::cout << *parr << '\n';
  std::cout << *arr << '\n';
  std::cout << &arr[0] << '\n';
  std::cout << &arr[2] << '\n';
  std::cout << &parr[1] << '\n';
  for(int i=0;i<sizeof(arr)/sizeof(string);i++,parr++)
  {
    std::cout << *parr << " "<< flush;
  };
  std::cout << endl;
// use the while loop to reach element//
string *parrelem= arr;
string *parrend= &arr[2];

while (true) {

std::cout << *parrelem << " " << flush;
if (parrelem==parrend) {
  break;
}
parrelem++;
}
std::cout << endl;
  return 0;
}
