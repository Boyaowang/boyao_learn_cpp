#include <iostream>
#include <vector>
using namespace std;

int &get(int *arr, int index){
  return arr[index];
}

int main(int argc, char const *argv[]) {
  int arr[2]= {0,1};
  get(arr,0)=999;
  std::cout << arr[0] << '\n';
  return 0;
}
