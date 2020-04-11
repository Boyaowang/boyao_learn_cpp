#include <iostream>
using namespace std;

int* arrdef()
{
  int* arr;
  arr=new int[10];
  return arr;
}

int* arrvalue(int* arr)
{
  for (int i = 0; i < 10; i++) {
    arr[i]=i;
  }
  return arr;
}

int main(int argc, char const *argv[]) {

  int* arr=arrdef();
  /*for (int i = 0; i < 10; i++) {
    arr[i]=i;
  }*/
  arr= arrvalue(arr);
  for (int i = 0; i < 10; i++) {
    std::cout << arr[i] << '\n';
  }

  return 0;
}
