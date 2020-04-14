#include <iostream>
using namespace std;

template<typename T>
class boyao
{
public:
  boyao(T a){
    std::cout << a << " is not an int" << '\n';
  }
};

// Here comes our specialization
template<>
class boyao<int>
{
public:
  boyao(int a){
    std::cout << a << " is an int" << '\n';
  };
};

int main(int argc, char const *argv[]) {
  boyao<string> stringval("wby");
  boyao<int> intval(555);
  return 0;
}
