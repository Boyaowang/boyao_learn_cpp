#include <iostream>
using namespace std;
#include "functions.h"

// constructor //

calculator::calculator()
{
  std::cout << "Thanks for using this program!!" << '\n';
}

// destructor //

calculator::~calculator()
{
  std::cout << "Byebye!!" << '\n';
}

double calculator::mult(double a, double b){
  double c=a*b;
  return c;
}

double calculator::divide(double a, double b){
  double c=a/b;
  return c;
}

double calculator::plus(double a, double b){
  double c=a+b;
  return c;
}

double calculator::minus(double a, double b){
  double c=a-b;
  return c;
}


cat::cat(){};
cat::~cat()
{
  std::cout << "cat is sleeping" << '\n';
};

void cat::catname() {
  string name;
  cout<< "The mane of the cat is " << endl;
  cin >> name ;
  cout << "The name you entered is: "<< name << endl;
}
