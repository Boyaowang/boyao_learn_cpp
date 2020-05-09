#include <iostream>
using namespace std;

class animal {
private:

public:
  animal (){};
  virtual ~animal (){};

  virtual void speak() = 0;
  virtual void run() = 0;
};

class dog:public animal{
private:

public:
  dog (){std::cout << "This is a dog" << '\n';};
  virtual ~dog (){};
  virtual void speak(){
    std::cout << "woff!!" << '\n';
  }
};

class beagle:public dog{
private:

public:
  beagle (){};
  virtual ~beagle (){};

  void run(){
    std::cout << "Beagle run" << '\n';
  }
};

void run(animal& obj)
{
  obj.run();
}



int main(int argc, char const *argv[]) {
//  dog wangwang;
  beagle wang;
  dog *zheng;
  zheng = &wang;
  zheng->run();
  wang.run();
  run(wang);
  return 0;
}
