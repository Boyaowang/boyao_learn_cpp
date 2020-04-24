#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[]) {

  string fileName = "text.txt";
  fstream myFile;
  myFile.open(fileName, ios::in);

  if (myFile.is_open()) {

    string line;
    //while (!myFile.eof()) {
    while (myFile) { //both of them are working

      getline(myFile, line);

      std::cout << line << '\n';

    };

    myFile.close();

  }
  else
  {
    std::cout << fileName <<" does not exit..." << '\n';
  }
  return 0;
}
