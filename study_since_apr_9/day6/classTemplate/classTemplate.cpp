#include <iostream>
using namespace std;

template <typename T>
class boyao
{
private:
  T a, b;
public:
  boyao(int va, int vb):
  a(va),
  b(vb){};
  T bigger();
};

template<typename T>
T boyao<T>::bigger()
{
  return (a>b?a:b);
}

int main(int argc, char const *argv[]) {
  boyao<int> test(20,46);
  std::cout << test.bigger() << '\n';
  return 0;
}
