#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  int currValue, value;
  if (cin >> currValue) {
    int cnt =1;
    while (std::cin >> value) {
      if (value==currValue) {
        ++cnt;
      }else
      {
        std::cout << currValue << " appers "<< cnt << '\n';
        cnt = 1;
        currValue =value;
      }
    }
    std::cout << currValue << " appers "<< cnt << '\n';

  }
  return 0;
}
