#include <iostream>
using namespace std;
int main(){
int a=5;
int b=10;
if (a==5 && (b==15 || (a+b==5)))
{
cout << "condition true" << endl;
}
else
{
cout << "condition false" << endl;
}
bool c;
c= a==1 && b==10 || (a+b==5);
cout << "c=" << c <<endl;
}
