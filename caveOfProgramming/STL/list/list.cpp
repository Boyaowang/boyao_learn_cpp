#include <iostream>
#include <list>

using namespace std;

int main(int argc, char const *argv[]) {

  list<int> numbers;

  numbers.push_back(1);
  numbers.push_back(2);
  numbers.push_back(3);

  numbers.push_front(0);

//insert a number to the list
  list<int>::iterator it = numbers.begin();
  it++;
  numbers.insert(it,1999);

  for (list<int>::iterator it = numbers.begin(); it != numbers.end() ; it++) {
    std::cout << *it << '\n';
  }
  std::cout << "****************erase a number from a list****************" << '\n';
  //erase a number from a list
  list<int>::iterator iterase = numbers.begin();
  iterase++;
  numbers.erase(iterase);

  for (list<int>::iterator it = numbers.begin(); it != numbers.end() ; it++) {
    std::cout << *it << '\n';
  }




  return 0;
}
