#include <iostream>
#include <vector>
using namespace std;

class Example {
public:
    static constexpr double rate = 6.5;
    static const int vecSize = 20;
    static std::vector<int> vec;

};

constexpr double Example::rate;
vector<int> Example::vec(Example::vecSize);

int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
