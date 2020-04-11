#include <iostream>
#include <sstream>
#include "streamout.h"
using namespace std;

void streamout::nameout(int age, string name)
{
stringstream ss;
ss<< "Name is: ";
ss<< name;
ss<< "; Age is: ";
ss<< age;
std::cout << ss.str() << '\n';
};
