#include <iostream>
#include <vector>
#include <list>
using namespace std;

template<typename T>
void printContainer(const T &v) {
  for(auto value:v)
  {
    std::cout << value << '\n';
  }
}

template<typename T>
void printIterContainer(const T &v) {
  for (typename T::const_iterator it = v.cbegin(); it != v.cend(); it++) {
    std::cout << *it << '\n';
  }
}

int main(int argc, char const *argv[]) {
  std::vector<int> v{1,2,3,4,5};
  printContainer(v);

  list<int> li{1,2,3,4,5};
  printContainer(li);

  printIterContainer(v);
  return 0;
}
