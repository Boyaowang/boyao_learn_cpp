/*
  fstream binaryFile;
  binaryFile.open("k", ios::binary|ios::in);
  if (binaryFile.is_open()) {
    std::cout << "bin file is open" << '\n';
  }
  string line;

  while (binaryFile) {
    getline(binaryFile, line);
    //std::cout << line << '\n';
  }
  */ //Just for fun

#include <iostream>
#include <fstream>

struct dataStruct
{
  int age;
  const char* name;
};

using namespace std;
//*******************************************************//
int main(int argc, char const *argv[]) {

  dataStruct dataBin{20, "hehe"};

  string fileName = "data.bin";

  ofstream outputFile(fileName);

  if (!outputFile.is_open()) {
    std::cout << "The file cannot be open" << '\n';
  };

  outputFile.write((char*) &dataBin, sizeof(dataBin));

  outputFile.close();

//input file from here **************

  dataStruct dataBininput;
  ifstream inputFile(fileName);

  if (!inputFile.is_open()) {
    std::cout << "The file cannot be read" << '\n';
  };

  inputFile.read((char*) &dataBininput, sizeof(dataBin));

// (char*) is a type casting

  std::cout << dataBininput.name << '\n';

  inputFile.close();

  return 0;
}
