#include <iostream>
using namespace std;

template<typename T>
class dimension {
private:
  /* data */

public:
  dimension (){};
  virtual ~dimension (){};
};

typedef dimension<int> dimensionInt;

int main(int argc, char const *argv[]) {
  dimensionInt zixin;
  return 0;
}
