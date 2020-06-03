#include <iostream>
using namespace std;

int iArr[3]{1,2,3};
typedef int (*parrten)[3];
parrten arrtenFunc(int (&arr)[3]){
  return &arr;
};

int (*parrFunc(int (&arr)[3]))[3]{
  return &arr;
}

decltype(iArr) *parrFunc2(int (&arr)[3])
{
  return &arr;
}

auto parrFunc3(int (&arr)[3])->int(*)[3]{ //or ->parrten or decltype(iArr) *
  return &arr;
}

//reference to an array function
typedef int (&Rarr)[3];

Rarr rarrFunc(int (&arr)[3])
{
  return arr;
}

int main(int argc, char const *argv[]) {

  std::cout << (*arrtenFunc(::iArr))[2] << '\n';
  std::cout << (*parrFunc(::iArr))[2] << '\n';
  std::cout << (*parrFunc2(::iArr))[2] << '\n';
  std::cout << (*parrFunc3(::iArr))[2] << '\n';
  std::cout << rarrFunc(::iArr)[2] << '\n';

  return 0;
}
