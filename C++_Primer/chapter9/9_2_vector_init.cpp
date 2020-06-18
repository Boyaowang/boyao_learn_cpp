#include <iostream>
#include <vector>
#include <list>
#include <deque>
using namespace std;

class test {
private:
  /* data */

public:
  test (int name){};
  virtual ~test (){};
};

int main(int argc, char const *argv[]) {
  std::vector<test> v(10,1212);
  std::vector<int> vi{1,2,4,5,7};
  vi.insert(vi.end(),9);
  for(auto value: vi)
  {
    std::cout << value << '\n';
  }

  list<deque<int>> ld;
  return 0;
}
