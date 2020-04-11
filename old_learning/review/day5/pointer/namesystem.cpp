#include <iostream>
#include "namesystem.h"
#include <sstream>
using namespace std;

namesystem::namesystem(){
  int age = 95; string name = "kk";
  //std::cout << "/* message */" << '\n';
};

namesystem::namesystem(int age, string name):name(name),age(age)
{
  //this->name=name1;
  //this->age=age1;
};

void namesystem::nameout()
{
stringstream ss;
ss<< "Name is: ";
ss<< name;
ss<< "; Age is: ";
ss<< age;
std::cout << ss.str() << '\n';
};
