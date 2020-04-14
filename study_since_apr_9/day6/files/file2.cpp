#include <iostream>
#include <fstream>
using namespace std;

// we are going to play with files today

int main(int argc, char const *argv[]) {
  ofstream boyaoFile("members.txt");

  std::cout << "Enter members name, age and gender" << '\n';
  std::cout << "press CTRL+c to quit" << '\n';

string name;
int age;
string gender;

while (std::cin >> name >> age >> gender) {
  boyaoFile << name << " " << age << " " << gender <<endl;
}

boyaoFile.close();
  return 0;
}
