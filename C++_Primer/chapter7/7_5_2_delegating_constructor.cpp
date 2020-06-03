#include <iostream>
using namespace std;

class test {
private:
  int a, b, c;

public:
  test(int a, int b, int c):a(a),b(b),c(c){
    std::cout << "No.1" << '\n';
  };
  test():test(1,2,3){std::cout << "No.2" << '\n';};
  test(istream& is):test(){
    std::cout << "No.3" << '\n';
  };
  virtual ~test (){};
};

int main(int argc, char const *argv[]) {
  test boyao(cin);
  return 0;
}
