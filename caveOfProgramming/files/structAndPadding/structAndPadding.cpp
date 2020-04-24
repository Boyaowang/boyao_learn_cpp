#include <iostream>
using namespace std;

#pragma pack(push,1) //save memory....but waste cpu cycle...
#pragma pack(pop)
int main(int argc, char const *argv[]) {
  struct foods
  {
    string pudding;
    int mango;
    char apple;
  };

  struct foods2
  {
    char apple;
    string pudding;
    int mango;
    // guess how many bytes are needed
  };

  struct foods3
  {
    char apple;
    char mango;
    string pudding;

    // guess how many bytes are needed
  };

  struct foods4
  {
    char apple;
    char mango;
    char bananas;

    // guess how many bytes are needed
  };


  std::cout << "size of foods " << sizeof(foods) << '\n';
  std::cout << "size of foods2 " << sizeof(foods2) << '\n'; //
  std::cout << "size of foods3 " << sizeof(foods3) << '\n'; //
  std::cout << "size of foods4 " << sizeof(foods4) << '\n'; //


  cout << "Size of const char* : " << sizeof(const char*) << endl;
  cout << "Size of char : " << sizeof(char) << endl;
  cout << "Size of int : " << sizeof(int) << endl;
  cout << "Size of string : " << sizeof(string) << endl;
  cout << "Size of short int : " << sizeof(short int) << endl;
  cout << "Size of long int : " << sizeof(long int) << endl;
  cout << "Size of float : " << sizeof(float) << endl;
  cout << "Size of double : " << sizeof(double) << endl;
  cout << "Size of long double : " << sizeof(long double) << endl;
  cout << "Size of wchar_t : " << sizeof(wchar_t) << endl;

  return 0;
}
