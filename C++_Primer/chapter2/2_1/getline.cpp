#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[]) {
  string line;
  while (getline(std::cin, line)) {
    std::cout << line << endl;
  }
  return 0;
}
