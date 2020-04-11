#include<iostream>
using namespace std;

class A
{
public:
  A()  { cout << "A's constructor called" << endl; }
};

class B
{
public:
  B()  { cout << "B's constructor called" << endl; }
  void outputname() {std::cout << "name is" << '\n';}
  ~B() {cout << "End of B" << endl;}
};

class C: public B, public A  // Note the order
{
public:
  C()  { cout << "C's constructor called" << endl; }
};

int main()
{
    C c;
    c.outputname();
    return 0;
}
