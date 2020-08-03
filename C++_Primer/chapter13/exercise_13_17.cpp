#include <iostream>

class numbered {
private:
  int mysn;
  static int unique;
public:
  friend void f(const numbered &);
  numbered ():mysn(unique){};
  // copy constructors
  numbered(numbered &numberedcp){
    this->mysn = ++unique;
    std::cout << "called copy constructor" << '\n';
  };
  numbered &operator =(numbered &obj){
    this->mysn = ++obj.unique;
    std::cout << "called =" << '\n';
  };
  virtual ~numbered (){};
};

int numbered::unique = 10;

void f(const numbered& s) {
    std::cout << s.mysn << std::endl;
}

int main()
{
    numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);
}
