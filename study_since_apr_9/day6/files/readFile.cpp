#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[]) {
  ifstream boyaoFile("members.txt");

  string name;
  int age;
  string gender;

  std::cout << "Member infomation:" << '\n';


  while (boyaoFile >> name >> age >> gender) {
    std::cout << name << " " << age << " " << gender << '\n';
  }
  return 0;
}
