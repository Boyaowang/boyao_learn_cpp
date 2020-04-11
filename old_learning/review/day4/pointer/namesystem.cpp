#include <iostream>
#include "namesystem.h"
#include "streamout.h"
using namespace std;

namesystem::namesystem(){
  int age = 95; string name = "kk";
  streamout person1;
  person1.nameout(age,name);
  //std::cout << "/* message */" << '\n';
};

namesystem::namesystem(int age, string name)
{
  streamout person2;
  person2.nameout(age,name);
}
