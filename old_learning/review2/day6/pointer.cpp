#include <iostream>
#include <cstring>
using namespace std;

void modiptr(int* ptr)
{
  for (int i = 0; i < 8; i++) {
    ptr[i]=i ;
  }
  for (int i = 0; i < 8; i++) {
    std::cout << ptr[i]<< '\n';
  }
};

int main(int argc, char const *argv[]) {
  int* ptr = new int[8];
  memset(ptr,-1,4);
 for (int i = 0; i < 8; i++) {
   std::cout << ptr[i] << '\n';
 }
modiptr(ptr);
int a=9;
int* ptr2 = &a;
int* Ptr2 = ptr2;
*Ptr2=999;
std::cout << "value of a " << a << '\n';
std::cout << "size of a int pointer"<< sizeof(ptr2) << '\n';
  return 0;
}
