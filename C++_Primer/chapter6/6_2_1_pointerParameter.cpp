#include <iostream>
#include <vector>
using namespace std;

void changeValue(int *pvalue) {
  *pvalue = 999;
}

void test(int)
{
  std::cout << "This is an int" << '\n';
};

template<class T>
void print(const T *beg, const T *end) {
  while (beg!=end) {
    std::cout << *beg << '\n';
    beg++;
  }
}

template<class T>
void rangePrint(const T &arr)
{
  for(auto elem: arr)
  {
    std::cout << elem << '\n';
  }
}



int count(std::vector<int>, std::vector<int>,  char);

int main(int argc, char const *argv[]) {
  // int a =9;
  // int* pa =&a;
  // //changeValue(pa);
  // changeValue(&a);
  // std::cout << a << '\n';
  int iArr[3]{0,2,999};
  print(begin(iArr),end(iArr));
  string sArr[2]{"name ", "boyao"};
  print(begin(sArr),end(sArr));
  std::cout << end(iArr)-begin(iArr) << '\n';
  rangePrint(sArr);
  return 0;
}
