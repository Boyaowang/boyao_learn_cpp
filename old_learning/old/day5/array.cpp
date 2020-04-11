#include<iostream>
using namespace std;

int main (){
	int arrayL;
	cout << "The length of the array is: " << endl;
	cin >> arrayL;
	double value[arrayL];
	for (int i=0;i<=(arrayL-1);i++)
	{   
            cout << "Please input " << i+1 << " th value for the array" << endl;
            cin >> value[i];
	  if (i==arrayL)
	  {
		cout << "The array is full" << endl;
	  }	
	}
		cout << "The array you input is: " << endl;
	for (int j=0;j<=(arrayL-1);j++)
	{
                cout << value[j];
	}	
	cout << endl;
return 0;
}
