#include <iostream>
#include <fstream>
using namespace std;

// STRORY 1
/*
int main(int argc, char const *argv[]) {

  string fileName = "text.txt";

  ofstream myfile;

  myfile.open(fileName);

  if (myfile.is_open()) {
    myfile << "Hi Boyao!" << endl;
    myfile << "Do not miss her.." << endl;
  }else
  {
    std::cout << "Cannot create file" << '\n';
  }
  return 0;
}
*/

// STRORY 2
/*
int main(int argc, char const *argv[]) {

  string fileName = "text.txt";

  fstream myfile;

  myfile.open(fileName, ios::in); // looooook here please
  if (myfile.is_open()) {
    myfile << "Hi Boyao!" << endl;
    myfile << "Do not miss her.." << endl;
  }else
  {
    std::cout << "Cannot read file" << '\n';
  }
  return 0;
}
*/


// STRORY 2
int main(int argc, char const *argv[]) {

  string fileName = "text.txt";

  fstream myfile;

  myfile.open(fileName, ios::out); // looooook here please
  if (myfile.is_open()) {
    myfile << "Hi Boyao!" << endl;
    myfile << "Do not miss her.." << endl;
  }else
  {
    std::cout << "Cannot read file" << '\n';
  }
  return 0;
}
