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
  virtual void attack(){};
};

class Ninja:public Enemy
{
public:
  void attack()
  {
    std::cout << "Ninja chop -"<< attackPower << "HP" << '\n';
  };
};

class Monster:public Enemy
{
public:
  void attack()
  {
    std::cout << "Monster bite -"<< attackPower << "HP" <<'\n';
  };
};

int main(int argc, char const *argv[]) {
  Ninja n;
  Monster m;
  Enemy* enemy1 = &n;
  Enemy* enemy2 = &m;
  enemy1->setAttackPower(20);
  enemy2->setAttackPower(50);
  enemy1->attack();
  enemy2->attack();
  return 0;
}
