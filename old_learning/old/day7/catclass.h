#ifndef CATCLASS_H_H
#define CATCLASS_H_H
#include <iostream>

using namespace std;

class cat{
	private:
        bool happy;
				string nameofcat;
	public:

        void mimi();
        char name();
        void makeHappy();
        void makeUnhappy();
      	void mood();

	// constructor //
	cat();
	// destructor//
	~cat();
};
#endif
