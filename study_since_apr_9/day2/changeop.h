#ifndef CHANGE_OP_
#define CHANGE_OP_

class changeop{
public:
  int num=0;
  changeop();
  changeop(int a);
  changeop operator+(changeop obj);
  changeop add(changeop obj);
};

#endif
