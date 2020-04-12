#ifndef BOYAO_H_
#define BOYAO_H_

class boyao
{
public:
  int regval; const int constval;
  //constructor
  boyao(int a, int b);

  // destructor
  ~boyao();

  void nonconst();
  void constfunc() const;
};

#endif
