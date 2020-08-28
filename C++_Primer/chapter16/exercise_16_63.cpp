#include <iostream>
#include <vector>

using namespace std;

template<typename T>
size_t count(const std::vector<T> &v,  T t)
{
  size_t cnt = 0;
  for(auto value:v)
  {
    if (value == t) {
      cnt++;
    }
  }
  return cnt;
}

template<>
size_t count(const std::vector<const char*> &v, const char* t)
{
  size_t cnt = 0;
  for(auto value:v)
  {
    if (value == t) {
      cnt++;
    }
  }
  std::cout << "specialize" << '\n';
  return cnt;
}


int main(int argc, char const *argv[]) {
  std::vector<int> v{1,3,4,5,7,8,9,4,3,2,4,5,4,2,5,7,7,4,4,1,6,8};
  std::cout << count(v,7) << '\n';
  std::vector<const char*> vcc = { "alan", "alan", "alan", "alan", "moophy" };
  std::cout << count(vcc, "alan") << std::endl;
  return 0;
}
