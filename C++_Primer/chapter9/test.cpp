#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
  vector<int> v{1,2,4,5,7};
  for (size_t i = 0; i < v.size(); i++) {
    std::cout << v[i-1] << " "<<  &v[i-1] << " ";
  }
  std::cout<< '\n';
  v.insert(v.begin()+2,9999);
  for (size_t i = 0; i < v.size(); i++) {
    std::cout <<  v[i-1] << " " << &v[i-1] << " ";
  }

}
