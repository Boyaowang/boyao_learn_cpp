#include <iostream>
#include "functionre.h"
using namespace std;

int main()
{
  functions testp;
  int value=5;
  int valuearray[]={111,2,3};
  string stringarray[]={"apple","watch","TV"};
  int *pvalue=&value;
  //int *ppvalue= valuearray;
  cout << *pvalue << " w.r.t. address: "<< &pvalue<< "but it points to" << pvalue <<endl;
  testp.output(pvalue);
  cout << "value becomes:" << value << " w.r.t. address: "<< &value << endl;
  cout << "ppvalue is "<< stringarray << endl;
}
