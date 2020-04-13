#include <iostream>
#include "people.h"
using namespace std;

people::people(string Name, birthday Dateofbirth)
: name(Name),
dateofbirth(Dateofbirth)
{
  std::cout << "initialise people" << '\n';
};

void people::printpeopleinfo()
{
  std::cout << "Name is: "<< name << '\n';
  dateofbirth.printbirthday();
}
