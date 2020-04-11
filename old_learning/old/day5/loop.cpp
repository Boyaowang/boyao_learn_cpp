#include <iostream>
using namespace std;
int main(){
	int a=1;
	while(a<5){
		cout << "stupid"<< a << endl;
		a++;
	}
	int i=1;
	do{
		cout << "crazy"<< i << endl;
		i++;
	}while(i<5);
	for(int j=1;j<=5;j++)
	{
		cout << "funny"<< j << endl;
	}
	/// password system ///	
	const string password1="hello";
	const string password2="seeya";
	string input1;
	while(input1!=password1){
		cout << "enter your password: " << endl;
		cin >> input1;
		if (input1!=password1){  
		cout << "wrong password!!! " << endl;
		}
	}

	cout << "your first password is correct!!" << endl;

	string input2;
	/*
	while(input2!=password2){
		cout << "enter your password: " << endl;
		cin >> input2;
		if (input2!=password2){  
		cout << "wrong password!!! " << endl;
		}
	}
        */
	for (int k=1;input2!=password2;k++)
	{
		cout << "enter your password: " << endl;
		cin >> input2;
		if (input2!=password2){  
		cout << "wrong password!!! " << endl;
	}
		if (k>3)
		{
			cout << "permision denied" << endl;
			break;
		}
	}
	if (input2==password2)
	{
	cout << "your second password is correct!!" << endl;
	}
// for loop with continue //
        string input3;
	const string password3="haha";
	for (int m=1;input3!=password3;m++)
	{
		cout << "enter your password: " << endl;
		cin >> input3;
	//	if (m>3)
	//	{
	//	cout << "permission denied" << endl;
	//	break;
	//	}
		if (input3!=password3)
		{  
		cout << "wrong password!!! " << endl;
		if (m>3)
		{
		cout << "permission denied" << endl;
		break;
		}
		continue;
		}
        	cout << "your third password is correct!!" << endl;
	}


	return 0;
}
