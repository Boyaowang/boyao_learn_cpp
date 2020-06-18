#include <iostream>
#include <vector>
using namespace std;

int sumVec(std::vector<string> vs)
{
  int sum=0;
  for(auto const value : vs)
  {
    sum += stoi(value);
  }
  return sum;
}

int main(int argc, char const *argv[]) {
  std::vector<string> v{"1","2","3","4","5"};
  std::cout << sumVec(v) << '\n';
  return 0;
}
