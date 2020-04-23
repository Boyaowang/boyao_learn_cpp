#include <iostream>
#include <exception>
using namespace std;

class myExceptions:public exception {
private:
public:
  virtual const char* what() const throw()
  {
    return "strange..";
  }
  myExceptions()
  {

  };
  myExceptions(int a)
  {
     std::cout << "value a "<< a << '\n';
  };
  myExceptions returnEmptyConstructor()
  {
    return myExceptions();
  }

  myExceptions returnConstructor(int b)
  {
    return myExceptions(b);
  }

}boyao;


int main(int argc, char const *argv[]) {

  //std::cout << boyao.what() << '\n';
  try
  {
    throw myExceptions();
  }catch(myExceptions& a)
  {
    std::cout << a.what() << '\n';
  }

  myExceptions wang(111);
  myExceptions WANG=wang.returnConstructor(1111);
  return 0;
}
