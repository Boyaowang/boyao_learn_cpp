#include <iostream>
#include <memory>
using namespace std;

class DebugDeleter {
private:
  ostream &os;

public:
  DebugDeleter (ostream &os = cerr):os(os){};
  template<typename T>
  void operator()(T *p)
  {
    std::cout << "delete the pointer" << '\n';
    delete p;
  }
  virtual ~DebugDeleter (){};
};

int main(int argc, char const *argv[]) {
  int *p = new int;
  //DebugDeleter()(p);
  DebugDeleter pointerDeleter;
  pointerDeleter(p);

  unique_ptr<int,DebugDeleter> p2(new int, pointerDeleter);
  unique_ptr<int,DebugDeleter> p3(new int, DebugDeleter());
  return 0;
}
