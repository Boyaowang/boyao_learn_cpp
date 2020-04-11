#include <iostream>
using namespace std;

class cat
{
public:
  //constructor
  cat(){std::cout << "This is a cat" << '\n';};
  //copy constructor
  cat(const cat& cat2){std::cout << "This is a copied cat!" << '\n';};

  void catref(int &value)
  {
    std::cout << "Please input a value" << '\n';
    std::cin >> value;
    std::cout << "The value you input is " << value << '\n';
  }
};


int main(int argc, char const *argv[]) {
  cat cat1;
  int ncat;
  //ncat=8;
  cat1.catref(ncat);
  std::cout << "Check ncat "<<ncat << '\n';
  //cat cat2=cat1;
  cat cat2(cat1);
  return 0;
}
