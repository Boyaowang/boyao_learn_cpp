#include <iostream>
using namespace std;

int main()
{
  int value;
  const int value_r=3;
  std::cout << "please input a value" << '\n';
  std::cin >> value;
  switch (value) {
    case 4:
    std::cout << "Correct value, the value is 4" << '\n';
    break;
    case value_r:
    std::cout << "Correct value, the value is 3" << '\n';
    break;
    case 7:
    std::cout << "Correct value, the value is 7" << '\n';
    break;
    case 9:
    std::cout << "Correct value, the value is 9" << '\n';
    break;
    default:
    std::cout << "undefined value" << '\n';
  }
  return 0;
}
