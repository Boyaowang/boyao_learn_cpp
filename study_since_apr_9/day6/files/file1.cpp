#include <iostream>
#include <fstream>
using namespace std;

// we are going to play with files today

int main(int argc, char const *argv[]) {
  ofstream boyaoFile("Jiechen.txt");//("Jiechen.txt", std::ofstream::out);
  //boyaoFile.open("Jiechen.txt");
  if (boyaoFile.is_open()) {
    boyaoFile << "One of my best friend is Boyao. I am also his best friend forever!!\n";
    boyaoFile << "We will trust and believe each other forever!!\n";
  } else {
    std::cout << "ERROR!!" << '\n';
  }
  boyaoFile.close();
  return 0;
}
