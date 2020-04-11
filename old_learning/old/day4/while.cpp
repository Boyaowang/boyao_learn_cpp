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
	/// password system ///	
	const string password="hello";
	string input;
	while(input!=password){
		cout << "enter your password: " << endl;
		cin >> input;
	}

	cout << "your password is correct!!" << endl;

	return 0;
}
