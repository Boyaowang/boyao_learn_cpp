#include <iostream>
#include "birthday.h"
#include "people.h"
using namespace std;

int main(int argc, char const *argv[]) {
  birthday birth_boyao(18,01,1995);
  birth_boyao.printbirthday();
  people boyao("boyao",birth_boyao);
  boyao.printpeopleinfo();
  return 0;
}
