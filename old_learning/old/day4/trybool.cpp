#include <iostream>
using namespace std;
int main(){
bool bValue=true;
bool fValue=false;
string tryValue="true";
//char cValue;// ASCII 
cout << "This is a string "<< tryValue << endl;
cout << "This is a bool result "<< bValue << endl;
int ValueforcValue;
cout << "Which ASCII you want to check: "; cin >>  ValueforcValue;
char cValue=ValueforcValue;// ASCII
cout << "This is a char result of ASCII you want: "<< cValue << endl;
cout << "This is a char result of ASCII you want: "<< (char)ValueforcValue << endl;
return 0;
}
