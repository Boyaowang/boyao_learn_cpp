#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

struct peopleInfo {
  string name;
  std::vector<string> phoneNo;
};

int main(int argc, char const *argv[]) {

  ifstream inputFile("contacts");
  string line, phoneNumbers;
  std::vector<peopleInfo> peopleList;

  while (getline(inputFile, line)) {

    peopleInfo people;
    istringstream sparseLine(line);
    sparseLine >> people.name;

    while(sparseLine>>phoneNumbers){
      people.phoneNo.push_back(phoneNumbers);
    }

    peopleList.push_back(people);

  }

  ofstream output("testContacts");
  for(auto value : peopleList)
  {
    std::cout << value.name << " ";
    output <<  value.name << " ";
    for(auto phoneNo : value.phoneNo)
    {
      std::cout << phoneNo << " ";
      output << phoneNo << " ";
    }
    std::cout << '\n';
    output << '\n';
  }

  ostringstream sortNames, sortNumbers;



  return 0;
}
