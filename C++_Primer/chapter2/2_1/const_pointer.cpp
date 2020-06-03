#include <iostream>
#include <string>
using namespace std;
//using std::string;

int main(int argc, char const *argv[]) {
  string name;
  getline(cin,name);
  string name2;
  getline(cin,name2);
  string names = name + name2;
  std::cout << names << '\n';
  const int buffer = 1024;
  const int *pbuffer = &buffer;
  pbuffer++;
  std::cout << buffer << '\n';
  std::cout << *pbuffer << '\n';
  pbuffer--;
  std::cout << *pbuffer << '\n';

  double alpha = 0.6;
  const double *palpha = &alpha;
  alpha+=0.2;
  std::cout << *palpha << '\n';

  double *const palpha_const = &alpha; // palpha_const's address cannot be changed but the value in this address can be changed
  *palpha_const-=0.1;
  std::cout << alpha << '\n';
  const int &r =90 ;

  std::cout << r << '\n';
  return 0;
}
