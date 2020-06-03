#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  int yourgrade = 59;
     cout << ((yourgrade>90) ? "super good"
    : ((yourgrade > 60)? "still good" : "resit...")) << endl;
    string s = "word";
    string pl = s + (s[s.size() - 1] == 's' ? "" : "s" );
    std::cout << pl << '\n';
    int bits = 0145;
    int bit2 = 0257;
    bits =	bits << 8;
  	//bits >> 3 ;
    cout << (bits & bit2) << endl;
    unsigned long quiz1 = 0;
    quiz1 |= (1UL << 2);
    quiz1 |= (1UL << 0);
    std::cout << quiz1 << '\n';
    int q = (~'q'<<6);
    std::cout << q << '\n';

    int x[10]; int *p =x;
    std::cout << sizeof(p)/sizeof(*p) << '\n';

    unsigned int m =10;
    int n =-99;
    std::cout << "it is converted to unsigned " <<m+n << '\n';
  return 0;
}
