#include<iostream>
using namespace std;
int main ()
{
	string namelist[2][3]={
		{"CPU","GPU","CFD"},
		{"bad","nice","strong"}
	};
/*	int i;
	int j;
	cout << "Please input the i -th and j -th of the 2D array";
	cin >> i;
	cin >> j;
	cout << "The item in " << i << " -th and " << j << "-th of the 2D array are" << namelist[i][j] << endl;
//        cout << "The value is " << namelist[i][j] << endl;
*/
       for (int k=0; k<(sizeof(namelist)/sizeof(namelist[0])); k++){
       for (int m=0; m<(sizeof(namelist[0])/sizeof(string)) ; m++){
       cout << namelist[k][m]<< " "<<flush;
       }
       cout << endl;       
       };
       cout << "size of the array is " << sizeof(namelist[0])/sizeof(string) << endl;  
       cout << "size of the array is " << sizeof(namelist)/sizeof(namelist[0]) << endl; 
       cout << "size of the array is " << sizeof(namelist)/sizeof(string) << endl; 
       return 0;
}
