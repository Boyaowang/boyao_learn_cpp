#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
  std::vector<string> vs{"I","am","an","am","an","idiot","or","not","fuck!!"};
  auto count = count_if(vs.begin(),vs.end(),[](string s)->bool{
    if (s.size()>3) {
      return true;
    }else
    {
      return false;
    }
  });
  std::cout << count << '\n';
  return 0;
}
