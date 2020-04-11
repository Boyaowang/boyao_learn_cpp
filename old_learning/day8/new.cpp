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
  ~cat(){std::cout << "End of the program!" << '\n';}
};


int main(int argc, char const *argv[]) {
  cat *cat1= new cat();
  int ncat=10;
  cat1->catref(ncat);
  std::cout << "size of the cat"<< sizeof(cat1) << '\n';
  delete cat1;
}
