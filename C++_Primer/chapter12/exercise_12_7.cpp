#include <iostream>
#include <vector>
#include <memory>
using namespace std;

shared_ptr<std::vector<int>> vecFunc()
{
  //std::vector<int> v{1,2,3};
  return make_shared<std::vector<int>>();
}

void print_vec(shared_ptr<std::vector<int>> p_vec) {
  int i=0;
  for (int i = 0; i < 3; i++) {
    p_vec->push_back(i);
  }
  for(auto value: *p_vec)
  {
    std::cout << value << '\n';
  }

}

int main(int argc, char const *argv[]) {
  print_vec(vecFunc());
  return 0;
}
