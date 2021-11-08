#include <iostream>
using namespace std;

class classForStatic
{
private:
    static int a;

public:
    static int b;
    classForStatic(/* args */);
    ~classForStatic();
    // static member functions
    static void printStatic();
    static void printStatic(int value);
    void modifyA(int value);
};

classForStatic::classForStatic(/* args */)
{
}

classForStatic::~classForStatic()
{
}

// declare the static member data
int classForStatic::a = 10;
int classForStatic::b = 15;

// declare the static member functions
void classForStatic::printStatic()
{
    cout << "a and b are " << a << " " << b << endl;
};

void classForStatic::printStatic(int value)
{
    cout << "a and b are " << a << " " << endl;
    cout << "value is " << value << endl;
};

void classForStatic::modifyA(int value)
{
    this->a = value;
};

// define the static

int main(int argc, char const *argv[])
{

    cout << "static member b is " << classForStatic::b << endl;

    classForStatic obj1;
    int value = 25;
    obj1.printStatic();

    classForStatic::printStatic();
    classForStatic::printStatic(value);
    // We are going to modify the private member a
    obj1.modifyA(value);
    classForStatic::printStatic();

    return 0;
}
