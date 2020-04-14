// virtual functions are actually template functions
// same functions from same type with different result

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
  };
  virtual void attack()=0;// This is a pure virtual function;
};

class Ninja:public Enemy
{
public:
  virtual void attack()
  {
    std::cout << "Ninja chop -"<< attackPower << "HP" << '\n';
  };
};

class Monster:public Enemy
{
public:
  virtual void attack()
  {
    std::cout << "Monster bite -"<< attackPower << "HP" <<'\n';
  };
};

class Monsterson: public Monster
{
public:
  virtual void attack()
  {
    std::cout << "Monster's son bite -"<< attackPower << "HP" <<'\n';
  };
};

int main(int argc, char const *argv[]) {
  Ninja n;
  Monster m;
  Monsterson ms;
  Enemy* enemy1 = &n;
  Enemy* enemy2 = &m;
  Enemy* enemy3 = &ms;
  enemy1->setAttackPower(20);
  enemy2->setAttackPower(50);
  enemy3->setAttackPower(99);
  enemy1->attack();
  enemy2->attack();
  enemy3->attack();
  return 0;
}
