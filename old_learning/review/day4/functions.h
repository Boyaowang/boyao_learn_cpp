#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

class calculator
{
public:
  // constructor //
  calculator();
  // destructor //
  ~calculator();
  double a; double b;
  double mult(double a, double b);
  double plus(double a, double b);
  double divide(double a, double b);
  double minus(double a, double b);
};

class cat
{
public:
  // constructor //
  cat();
  // destructor //
  ~cat();

  void catname();
};


#endif
