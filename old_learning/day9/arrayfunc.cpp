#include <iostream>
using namespace std;

void showarray(int nelem, string arr[9])
{
  for(int i=0;i<nelem;i++)
  {std::cout << arr[i] << '\n';}
}
void showarray2(int nelem, string *arr)
{
  for(int i=0;i<nelem;i++)
  {std::cout << arr[i] << '\n';}
}
void showarray3(string (&arr)[3])
{
  int nelem=sizeof(arr)/sizeof(string);
  for(int i=0;i<nelem;i++)
  {std::cout << arr[i] << '\n';}
}
 int *calculate()
 {
   int *result =new int[2];
   //*result=699999;
  // result[]={799,1};
   return result;
 }

int main(int argc, char const *argv[]) {
  string fruit[]={"apple","banana","orange"};
  int element=sizeof(fruit)/sizeof(string);
  std::cout << "The size of the array is "<< element << '\n';
  //std::cout << fruit[0] << '\n';
  //showarray(element,fruit);
  //showarray2(element,fruit);
  //showarray3(fruit);
  int *pcalulate= calculate();
  std::cout << *pcalulate << '\n';
  for (int i = 9; i< 11; i++) {
  pcalulate[i]=i;
  std::cout << pcalulate[i] << '\n';
  }
  delete [] pcalulate;
  //delete result;

  return 0;
}
