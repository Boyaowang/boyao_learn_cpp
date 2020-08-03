#include <iostream>
#include <memory>

using namespace std;

int main(int argc, char const *argv[]) {
  //unique_ptr<int[]> p(new int[10]);
  shared_ptr<int[]> p(new int[10],[](int *p){delete [] p;});
  for (size_t i = 0; i < 10; i++) {
    //p[i] = i;
    *(p.get()+i) = i;
  }

  for (size_t i = 0; i < 10; i++) {
    //std::cout << p[i] << '\n';
    std::cout << *(p.get()+i) << '\n';
  }

  p.reset();
  return 0;
}
