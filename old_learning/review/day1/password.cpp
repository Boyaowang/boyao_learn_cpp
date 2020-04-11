#include <iostream>
using namespace std;

int main()
{
  string password="hello";
  string input;
do {
  std::cout << "type your password: " << '\n';
  std::cin >> input;
  if(input!=password)
  {
    std::cout << "your password is wrong!! Try again!" << '\n';
    continue;
  }
  std::cout << "your password is correct!!" << '\n';
} while(input!=password);
}
