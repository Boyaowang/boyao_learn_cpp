#include <iostream>
using namespace std;

void print(const int ia[10]) {
for (size_t i = 0; i != 10; ++i)
   cout << ia[i] << endl;
}
int main(int argc, char const *argv[]) {
  string name1 = argv[0];
  string name2 = argv[1];
  string name3 = argv[2];
  string name = name1 + " " + name2 +" "+ name3;
  std::cout <<name << '\n';
  if (argv[1]="hi") {
    std::cout << "Hello world" << '\n';
  }

  int a[10]={0,1,2,3,4,5,6,7,8,9};
  print(a);
  return 0;
}
