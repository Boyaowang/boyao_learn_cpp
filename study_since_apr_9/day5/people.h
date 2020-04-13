#include <iostream>
using namespace std;
#include "birthday.h"
#ifndef PEOPLE_H
#define PEOPLE_H

class people
{
private:
  string name;
  birthday dateofbirth;
public:
  people(string Name, birthday Dateofbirth);
  void printpeopleinfo();
};

#endif
