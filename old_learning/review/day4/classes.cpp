#include <iostream>
using namespace std;
#include "functions.h"

int main()
{
 {
   calculator A;
// double x=5;
// double y=3;
 A.a=6; double x= A.a;
 A.b=9; double y= A.b;
 std::cout << "a= " << A.a << '\n';
 std::cout << "b= " << A.b << '\n';
 std::cout << "multiply: "<<A.mult(x,y) << '\n';
 std::cout << "divide: " << A.divide(x,y)<<'\n';
 std::cout << "plus: " <<A.plus(x,y)<< '\n';
 std::cout << "minus: " <<A.minus(x,y)<< '\n';
}

{
 cat mimi;
 mimi.catname();
}
 std::cout << "end of the programm" << '\n';
 return 0;
}
