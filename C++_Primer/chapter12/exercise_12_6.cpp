#include <iostream>
#include <vector>
using namespace std;

std::vector<int> *vecFunc()
{
  std::vector<int> *vec = new std::vector<int>{1,2,3};
  return vec;
}

void print_vec(std::vector<int> *p_vec) {
  for(auto value: *p_vec)
  {
    std::cout << value << '\n';
  }
  delete p_vec;
}

int main(int argc, char const *argv[]) {
  print_vec(vecFunc());
  return 0;
}
