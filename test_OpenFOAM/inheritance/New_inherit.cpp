#include <iostream>
#include <memory>
using namespace std;

#include "base.H"
#include "child1.h"

void callbase(const Base& baseObj) {
  std::cout << "success" << '\n';
}

int main(int argc, char const *argv[]) {
  callbase(child1());
  return 0;
}
