#ifndef NAMESETUP_H_
#define NAMESETUP_H_
#include <iostream>
using namespace std;

class namesystem
{
private:
  int age=0;
  string name="undefined";
public:
  namesystem();
  namesystem(int age, string name);
  void nameout();
};

#endif
