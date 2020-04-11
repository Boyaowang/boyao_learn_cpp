#include<iostream>

using namespace std;

#include "function.h"

       int getinput(){
	       cout << "Please input a value from 1,2 and 3: " << endl;
	       int input;
	       cin >> input;
	       return input;
       }

       void switchfunction(int yourchoice){
	       switch (yourchoice){
	       case 1:
		       cout << "stupid" << endl;
		       break;
	       case 2:
		       cout << "Okay" << endl;
		       break;
	       case 3:
		       cout << "Good!!" << endl;
		       break;
	       default:
		       cout << "Please choose 1,2 or 3" << endl;
	       }
       }
       void tryFunction(); // test prototype
int main ()
{
       tryFunction();
       tryFunction2();
       int input_=getinput();
       cout << "The value you input is " << input_ << endl;
       switchfunction(input_);
       return 0;
}

       void tryFunction()
       {
	       cout << "This is a function" << endl;
       }
