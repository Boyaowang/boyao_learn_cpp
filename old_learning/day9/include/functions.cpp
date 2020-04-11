#include "functions.h"
#include <iostream>
using namespace std;

int* newvalue::intarr(int n)
{
  int* value=new int[n];
  return value;
}

void newvalue::deletesigle(int* pointer)
{
  delete pointer;
}

void newvalue::deletearray(int* pointer)
{
  delete [] pointer;
}
