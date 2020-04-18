#include <iostream>
#include <fstream>
using namespace std;

//prototypes

void getWhatTheyWant(int& whatTheyWant);
void displayItems(int x);

// main function

int main(int argc, char const *argv[]) {
  int whatTheyWant;
  while (whatTheyWant!=4) {
    getWhatTheyWant(whatTheyWant);
    //std::cout << whatTheyWant << '\n';
    /*
    switch (whatTheyWant) {
      case 1://display plain items
      displayItems(whatTheyWant);
      break;
      case 2://display plain items
      displayItems(whatTheyWant);
      break;
      case 3://display plain items
      displayItems(whatTheyWant);
      break;
    }*/
    displayItems(whatTheyWant);
  };
  return 0;
}

void getWhatTheyWant(int& whatTheyWant)
{
  cout << "\n1 - just plain items" <<endl;
  cout << "2 - helpful items" <<endl;
  cout << "3 - harmful items" <<endl;
  cout << "4 - quit program \n" <<endl;
  std::cin >> whatTheyWant;
};

void displayItems(int x)
{
  ifstream items("objects.txt");
  string name;
  double power;
  if (x==1) {
    while (items>> name >> power) {
      if (power==0) {
        std::cout << "plain items name "<< name << "items power "<< power << '\n';
      };
  };
  };


  if (x==2) {
    while (items>> name >> power) {
      if (power>0) {
        std::cout << "helpful items name "<< name << "items power "<< power << '\n';
      };
  };
  };

  if (x==3) {
    while (items>> name >> power) {
      if (power<0) {
        std::cout << "harmful items name "<< name << "items power "<< power << '\n';
      };
   };
 };
};
