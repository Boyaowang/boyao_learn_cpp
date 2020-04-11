#include <iostream>
#include "shops.h"

using namespace std;

int main(int argc, char const *argv[]) {
 shops::shop1::dogs visit1;
 visit1.dogspeak();
 shops::shop2::dogs visit2;
 visit2.dogspeak();
 shops::Parray::parray dogsnum;
 int* arrs=dogsnum.parr();
 dogsnum.arrloop(arrs);
 dogsnum.rmem(arrs);
return 0;
}
