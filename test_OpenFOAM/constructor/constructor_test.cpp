#include <iostream>
using namespace std;

class test {
private:
  /* data */

public:
  test (const int a =999){};
  virtual ~test (){};
};

void Hasher
(
    const void *key,
    size_t length,
    unsigned initval
)
{
  std::cout << "/* message */" << '\n';
}

int compareInt( void *lhs,  void *rhs)
{
  const int *x = static_cast<int*>(lhs);  // convert void * to int * by assignment
  const int *y = static_cast<int*>(rhs);

  if (*x > *y) return 1;
  if (*x == *y) return 0;
  return -1;
}

int main(int argc, char const *argv[]) {
  test boyao;
  string axin("axin");
  // std::cout << axin.data() << '\n';
  Hasher(axin.data(),axin.size(),axin.size());
  void* a = &axin;
  string *b = static_cast<string*>(a);
  std::cout << *b << '\n';
  return 0;
}
