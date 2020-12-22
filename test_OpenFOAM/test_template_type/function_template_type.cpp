#include <iostream>
#include <vector>
using namespace std;

template<class T>
void print(std::vector<T> v) {
  for (size_t i = 0; i < v.size(); i++) {
    std::cout << v[i] << '\n';
  }
  T a =11;
  std::cout << a << '\n';
}

int main(int argc, char const *argv[]) {
  std::vector<int> vi;
  for (size_t i = 0; i < 10; i++) {
    vi.push_back(i);
  }

  print(vi);

  return 0;
}
