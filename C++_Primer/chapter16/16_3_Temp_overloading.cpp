#include <iostream>
#include <sstream>
using namespace std;

template<typename T>
string debug_rep(const T &t)
{
  ostringstream ret;
  ret << t;
  return ret.str();
}

template<typename T>
string debug_rep(T *p)
{
  std::cout << "pointer: "<< p;
  ostringstream ret;
  if (p) {
    ret << " " << debug_rep(*p) << '\n';
  } else {
    ret << "null_ptr" << '\n';
  }
  return ret.str();
}



int main(int argc, char const *argv[]) {
  string zixin("zixin");
  //std::cout << debug_rep(zixin) << '\n';
  const string *axin =&zixin;
  std::cout << debug_rep(&zixin) << '\n';
  std::cout << debug_rep(axin) << '\n';
  return 0;
}
