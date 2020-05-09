#include <iostream>
#include <vector>
using namespace std;

bool match(string text)
{
  return text.size()==3;
}

int countMatch(std::vector<string> list, bool(*matchFunc)(string))
{
  int count=0;
  for (std::vector<string>::iterator it = list.begin(); it != list.end(); it++) {

    if (matchFunc(*it)) {
      count++;
    }
  }
  return count;

}

void printCount(int value) {
  std::cout << value << '\n';
}

int main(int argc, char const *argv[]) {
  std::vector<string> numberList;
  numberList.push_back("one");
  numberList.push_back("two");
  numberList.push_back("three");
  numberList.push_back("four");
  numberList.push_back("five");
  numberList.push_back("six");
  numberList.push_back("seven");
  numberList.push_back("eight");
  numberList.push_back("nine");
  numberList.push_back("ten");

  printCount(countMatch(numberList, match));


  return 0;
}
