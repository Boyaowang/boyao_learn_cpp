#include <iostream>
using namespace std;

class canGoWrong
{
public:
  canGoWrong()
  {
    char* text = new char[9999999];
    delete text;
  };
};

class testAmpersand
{
public:
  int a = 6;
};
// This is a side story
void changeValue(testAmpersand& obj) //with &. value inside a class obj can be changed
{
  obj.a=999;
};

int main(int argc, char const *argv[]) {
  try{
    canGoWrong boyao;
  }catch(std::bad_alloc& e)
  {
    std::cout << e.what() << '\n';
  };

  testAmpersand boyao2;
  changeValue(boyao2);
  std::cout << boyao2.a << '\n';


  return 0;
}
