#include "changeop.h"

changeop::changeop()
{};

changeop::changeop(int a)
{
   num = a;
};

changeop changeop::add(changeop obj)
{
  changeop obj2;
  obj2.num=num+obj.num;
};

changeop changeop::operator+(changeop obj)
{
  changeop obj2;
  obj2.num=num+obj.num;
  //return obj2; not necessary
};
