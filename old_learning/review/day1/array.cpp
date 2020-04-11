#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int array1[3]={1,2,3};
  std::vector<int>array2;
  array2.resize(sizeof(array1)/sizeof(int));
  std::cout << "size of array2 is " << sizeof(array2)/sizeof(int)<< '\n';
}
