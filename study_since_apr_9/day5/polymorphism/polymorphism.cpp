// Study polymorphism //

#include <iostream>
using namespace std;

class Enemy
{
protected:
  int attackPower;
public:
  int setAttackPower(int a)
  {
    attackPower=a;
  }
};

class Ninja:public Enemy
{
public:
  void attck()
  {
    std::cout << "Ninja chop -"<< attackPower << "HP" << '\n';
  };
};

class Monster:public Enemy
{
public:
  void attck()
  {
    std::cout << "Monster bite -"<< attackPower << "HP" <<'\n';
  };
};

int main(int argc, char const *argv[]) {
  Ninja a;
  Monster b;
  /*
  a.setAttackPower(20);
  b.setAttackPower(50);
  a.attck();
  b.attck();
  */
  Enemy* ninja = &a;
  Enemy* monster = &b;
  ninja->setAttackPower(20);
  monster->setAttackPower(50);
  a.attck();
  b.attck();
  return 0;
}
