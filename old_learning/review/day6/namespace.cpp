#include <iostream>
using namespace std;

namespace namesys
{
  class name
  {
  public:
    void yourname(string name) {
     std::cout << "your name is: "<< name << '\n';
    }
  };
  class age
  {
  public:
    void yourage(int age1)
    {
      std::cout << "your age is: "<< age1 << '\n';
    }
  };
  class student:public name, public age
  {
  public:
    student(){std::cout << "The name and age of the student:" << '\n';}
  };
}


int main(int argc, char const *argv[]) {
  string name="wby"; int age=25;
  namesys::student boyao;
  boyao.yourname(name);
  boyao.yourage(age);
  return 0;
}
