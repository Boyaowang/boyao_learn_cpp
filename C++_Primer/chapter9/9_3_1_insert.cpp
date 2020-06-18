#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[]) {
  std::vector<int> v1{1,2,3,4,5};
  std::vector<int> v2{0,0,0};
  std::cout << *(v2.insert(v2.end(),v1.begin(),v1.end())) << '\n';
  for(auto value: v2)
  {
    std::cout << value << '\n';
  }
  std::vector<string> vs;
  auto it = vs.begin();
  string word;
  ifstream input("fuck");
  while (input >> word) {
    it = vs.insert(it,word);
  }
  for(auto value: vs)
  {
    std::cout << value << " ";
  }
  return 0;
}
