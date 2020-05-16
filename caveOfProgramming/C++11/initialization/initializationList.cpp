#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

class List {
private:
  std::vector<int> v;
  int a[4]{10,20,30,50};
public:

  void print(initializer_list<int>::iterator arg) {
    std::cout << *arg << '\n';
  }

  List(initializer_list<int> arg){
    for (initializer_list<int>::iterator it = arg.begin(); it != arg.end(); it++) {
      print(it);
    }
  };

  void plusAndMove(){
    int i=0;
    for(auto value:a)
    {
      v.push_back(value+10);
      i++;
      //std::cout << ":" << value << '\n';
    }
    for(auto value:v)
    {
      std::cout << ":" << value << '\n';
    }

  };

  virtual ~List(){};
};

int main(int argc, char const *argv[]) {
  List Boyao{10,20,30,50};
  Boyao.plusAndMove();

  return 0;
}
