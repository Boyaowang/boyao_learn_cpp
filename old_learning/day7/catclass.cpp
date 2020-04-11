#include <iostream>
#include "catclass.h"
using namespace std;


// constructor //
cat::cat(){
	cout << "Cat is created!!" << endl;
	cout << "name of your cat: " << endl;
	cin >> nameofcat;
	cout << "Her name is " << nameofcat << endl;
}
// Destructor //
cat::~cat(){
	cout << "Cat is destroyed!!" << endl;
}

void cat::mimi()
       {
	       cout << "miaomiaomiao!!!!" << endl;
       }
char cat::name()
{
	char catname;
	cout << "name of your cat: " << endl;
	cin >> catname;
	cout << "Her name is " << catname << endl;
  return catname;
}
void cat::mood()
{
  if (happy)
  {
    cout << nameofcat << " is a happy cat" << endl;
  }
  else
  {
    cout << "she wants to sleep....." << endl;
  }
}
void cat::makeHappy()
{
  happy=true;
}
void cat::makeUnhappy()
{
  happy=false;
}
