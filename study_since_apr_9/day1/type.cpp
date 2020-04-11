#include <iostream>

// template specializer
template<typename T>
class variableType
{
public:
  variableType(){std::cout << "This is not a char" << '\n';}
};

template<>
class variableType<char>
{
public:
  variableType(){std::cout << "This is a char" << '\n';}
};

// layer1
template<int>
struct layer1
{
  layer1(){std::cout << "This is layer 1"<< '\n';}
};

template<>
struct layer1<1>
{
  layer1(){std::cout << "In layer 1, you input 1." << '\n';}
};
// layer2
typedef variableType<int> type1;
//typedef type1<layer1> type2;
//template<type1>
struct layer2
{
  layer2(){std::cout << "This type is variableType" << '\n';}
};
template <int A, int B>
struct EqualityCheck {
    enum PerformCheck {
        CheckResult = (A == B),
        fuckyou = (A!=B)
    };
};
int main(int argc, char const *argv[]) {
  // Test template specializer
  variableType <char> boyao;
  variableType <int>Boyao;
  // layer1
  layer1<1> wby;
  type1 wbywby;
  EqualityCheck <1,1>wbywbywby;
  int a=wbywbywby.CheckResult;
  int b=wbywbywby.fuckyou;
  std::cout << a << '\n';
  std::cout << b << '\n';
  return 0;
}
