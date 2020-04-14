#include <iostream>
#include <fstream>
using namespace std;

// we are going to play with files today

int main(int argc, char const *argv[]) {
  ofstream boyaoFile;
  boyaoFile.open("Jiechen.txt");
  boyaoFile << "One of my best friend is Boyao. I am also his best friend forever!!\n";
  boyaoFile.close();
  return 0;
}
