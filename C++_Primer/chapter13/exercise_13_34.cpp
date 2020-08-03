#include <iostream>
#include "Message.H"

using namespace std;

int main(int argc, char const *argv[]) {
  Folder zixin;
  Message msg1("I love you");
  msg1.save(zixin);
  zixin.print();
  return 0;
}
