#include <iostream>
// see limit of different variables //
#include <limits>
#include <limits.h>
// for scientific value //
#include <iomanip>
using namespace std;
int main(){
int haha = 500;
float hahaf=123.4567;
double hahad=56789.1234;
cout << haha << endl;
cout << INT8_MAX << endl;
cout << INT_MAX << endl;
cout << scientific << hahad << endl;
cout << setprecision(20)  << hahad << endl;
cout << LLONG_MAX << endl;
cout << "size of int " << sizeof(int) << endl;
signed int sig=-5;
cout << "check signed int " << sig << endl;
// printf("%d\n", INT_MAX);
  
}

