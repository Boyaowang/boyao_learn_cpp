#include <iostream>
#include "functionre.h"
using namespace std;

// constructor
functions::functions()
{
  std::cout << "we are learning how to use pointer" << '\n';
}


void functions::output(int *input)
{
  cout << "You input: " << *input << endl;
  std::cout << "you want to change it to: " << '\n';
  std::cin >> *input;
  cout << "It is modified to: " << *input << "w.r.t. address: " << input << endl;
}

// destructor
functions::~functions()
{
  std::cout << "We know how to play that!!" << '\n';
}
