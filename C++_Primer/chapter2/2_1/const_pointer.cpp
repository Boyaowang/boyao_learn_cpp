#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  const int buffer = 1024;
  const int *pbuffer = &buffer;
  pbuffer++;
  std::cout << buffer << '\n';
  std::cout << *pbuffer << '\n';
  pbuffer--;
  std::cout << *pbuffer << '\n';

  double alpha = 0.6;
  const double *palpha = &alpha;
  alpha+=0.2;
  std::cout << *palpha << '\n';
  return 0;
}
