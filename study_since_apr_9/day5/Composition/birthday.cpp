#include <iostream>
#include "birthday.h"
using namespace std;

birthday::birthday(int d, int m, int y):
day(d),
month(m),
year(y)
{
  std::cout << "initialise your date of birth" << '\n';
};

void birthday::printbirthday()
{
  std::cout << "The birthday is:"<< day << "/"<< month << "/" << year << '\n';
};
