#include<iostream>
using namespace std;
int main ()
{
	string namelist[2][2]={
		{"CPU","GPU"},
		{"bad","nice"}
	};
	int i;
	int j;
	cout << "Please input the i -th and j -th of the 2D array";
	cin >> i;
	cin >> j;
	cout << "The item in " << i << " -th and " << j << "-th of the 2D array are" << namelist[i][j] << endl;
//        cout << "The value is " << namelist[i][j] << endl;

       for (int k=0; k<=1; k++){
       for (int m=0; m<=1; m++){
      cout << namelist[k][m]<< " "<<flush;
       }
      cout << endl;       
       };
	return 0;
}
