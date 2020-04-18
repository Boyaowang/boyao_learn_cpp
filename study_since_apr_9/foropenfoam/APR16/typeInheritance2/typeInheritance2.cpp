#include <iostream>
using namespace std;

class yourname
{
public:
  string name="boyao";
public:
  yourname()
  {std::cout << "yourname Constructor" << '\n';};
};


template<class nameclass>
class boyao
:public nameclass
{
public:
  boyao()
  {std::cout << "boyao Constructor" << '\n';}
 void printname()
 {
   std::cout << nameclass::name << '\n';
 };
};

typedef boyao<yourname> typeb;

template<class familymember>
class jiechenbaba
:public familymember
{
public:
  jiechenbaba()
  {std::cout << "typeb::printname()" << '\n';};

};

typedef jiechenbaba<boyao<yourname>> typea;


int main(int argc, char const *argv[]) {
  typea boyaoname;
  typeb boyao1111;
  //typeb boyaoname;
  //boyaoname.printname();
  boyaoname.printname();
  return 0;
}
