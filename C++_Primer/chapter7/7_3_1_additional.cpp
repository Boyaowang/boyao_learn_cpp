#include <iostream>
using namespace std;
//#include "screen.H"
#include "windows_mgr.H"

int main(int argc, char const *argv[]) {
  //screen::pos a =100;
  screen test;
  //test.printMutalble();
  test.move(1,1).set('#').display(cout);

  screen myScreen(5,3,'a');
  myScreen.move(1,1).set('#').display(cout);
  std::cout << '\n';
  myScreen.display(cout);

  return 0;
}
