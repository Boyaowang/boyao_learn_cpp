#include <iostream>
using namespace std;

template<typename  tt>
void output(tt value)
{
  std::cout << value << '\n';
}

int main(int argc, char const *argv[]) {
  output<string>("9.9");
  return 0;
}
