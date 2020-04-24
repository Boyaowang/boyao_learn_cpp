#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {

  std::vector<string> stringVector(5); // A vector which has 5 strings

  stringVector[1] = "dog";

  stringVector.push_back("add one");

  stringVector.push_back("add two");

  std::cout << stringVector[1] << " "<< stringVector[5] << " " << stringVector[6] << '\n';
  std::cout << "Size of the stringVector is " << sizeof(stringVector) << "The amount of elemnents insides is " << stringVector.size()<< '\n';

  std::vector<string> stringVector2; // A vector which has 5 strings

  stringVector2.push_back("one");

  stringVector2.push_back("two");

  std::cout << stringVector2[0] <<" "<< stringVector2[1] << '\n';

  std::cout << stringVector2.size() << '\n';
  for (int i = 0; i < stringVector2.size(); i++) {
    std::cout << stringVector2[i] << '\n';
  }

  std::vector<string>::iterator it = stringVector2.end(); // it is a pointer
  it--;
  std::cout << *it << '\n';

  for (std::vector<string>::iterator it = stringVector2.begin(); it<stringVector2.end(); it++) {
    std::cout << "iterator "<< *it << '\n';
  }
  return 0;
}
