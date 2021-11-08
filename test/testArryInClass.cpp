#include <iostream>
#include <vector>
using namespace std;

class arrClass {
private:
  std::vector<std::vector<int>> v;

public:
  arrClass (){
    // v={1,23};
    v.resize(5);
    for (auto it = v.begin(); it != v.end(); it++) {
      it->resize(2);
      for (auto it2 = it->begin(); it2 != it->end(); it2++) {
        std::cout << *it2 << '\n';
      }

    }
    v[3][1]=15;
    // std::cout << v[0][0] << '\n';
    for (auto it = v.begin(); it != v.end(); it++) {
      // it->resize(2);
      for (auto it2 = it->begin(); it2 != it->end(); it2++) {
        std::cout << *it2 << '\n';
      }

    }

  };
  virtual ~arrClass (){};
};


int main(int argc, char const *argv[]) {
  arrClass a;
  return 0;
}
