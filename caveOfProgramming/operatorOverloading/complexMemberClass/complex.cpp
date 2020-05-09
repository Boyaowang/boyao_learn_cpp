#include "complex.H"
#include <iostream>

namespace boyaoCalc
{
  complex::complex(const complex& obj){
    real = obj.real;
    imaginary = obj.imaginary;
    std::cout << "copy constructor run" << '\n';
  };

  const complex& complex::operator=(const complex& obj){
    real = obj.real;
    imaginary = obj.imaginary;
    std::cout << "run = " << '\n';
    return *this;
  };

  complex& complex::operator+(const complex& obj){
    real += obj.real;
    imaginary += obj.imaginary;
    std::cout << "run +" << '\n';
    return *this;
  };

/*  ostream& operator<<(ostream& out, complex& obj)
 {
      out << "("<< obj.getReal() << ", " << obj.getImaginary() << ")";
      return out;
  }
*/
}
