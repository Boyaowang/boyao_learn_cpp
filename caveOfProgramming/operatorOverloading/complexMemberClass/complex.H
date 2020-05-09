#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>
using namespace std;

namespace boyaoCalc{
class complex
{
private:
  double real;
  double imaginary;
public:

  complex(){};

  complex(double real, double imaginary)
  :real(real),imaginary(imaginary)
  {};

// copy constructor
  complex(const complex& obj);

// operator overloading
  const complex& operator=(const complex& obj);

  complex& operator+(const complex& obj);

// get real and imaginary values
  double getReal()
  {
    return real;
  };

  double getImaginary()
  {
    return imaginary;
  };
  virtual ~complex(){};

};

inline ostream& operator<<(ostream& out, complex& obj){
      out << "("<< obj.getReal() << ", " << obj.getImaginary() << ")";
      return out;
  };
}
#endif
