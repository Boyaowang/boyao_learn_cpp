#include <iostream>
#include <memory>
using namespace std;

class zixin {
private:
  /* data */

public:
  int ID_num = 0;
  zixin (){};
  virtual ~zixin (){};
  static shared_ptr<zixin> New(shared_ptr<zixin>& obj);
  virtual void printName()
  {
    std::cout << "zixin" << '\n';
  }
};

class boyao: public zixin {
private:
  /* data */

public:
  int ID_num =1;
  boyao (){};
  virtual ~boyao (){};
  virtual void printName()
  {
    std::cout << "boyao" << '\n';
  }
};

class xiaoboyao: public zixin {
private:
  /* data */

public:
  int ID_num =2;
  xiaoboyao (){};
  virtual ~xiaoboyao (){};
  virtual void printName()
  {
    std::cout << "xiaoboyao" << '\n';
  }
};

class parent {
private:
  void initialise(/* arguments */) {
    zixin_ = zixin_->New(zixin_);
  }
protected:
    shared_ptr<zixin> zixin_;

public:
  parent ():zixin_(nullptr){
    initialise();
  };
  virtual ~parent (){};
  int name()
  {
    return 0;
  }

  virtual void print(/* arguments */) {
    std::cout << "parents" << '\n';
  }

  static shared_ptr<parent> New(shared_ptr<parent>& obj);

};

class child1:public parent {
private:
  /* data */

public:
  child1 (){};
  virtual ~child1 (){};
  int name()
  {
    return 1;
  }
  void maxPrint(/* arguments */) {
    print();
  }
  virtual void print(/* arguments */) {
    std::cout << "child1" << '\n';
  }
};

class child2: public parent {
private:
  /* data */

public:
  child2 ():parent(){};
  virtual ~child2 (){};
  int name()
  {
    return 2;
  }
};

shared_ptr<parent> parent::New(shared_ptr<parent>& obj)
{
  switch (obj->name()) {
    case 0:
    std::cout << "case 0" << '\n';
    return shared_ptr<parent>(new child1());
    break;
    case 1:
    return shared_ptr<parent>(new child2());
    break;
  }
};

shared_ptr<zixin> zixin::New(shared_ptr<zixin>& obj)
{
  switch (obj->ID_num) {
    case 0:
    std::cout << "case 0" << '\n';
    return shared_ptr<zixin>(new boyao());
    break;
    case 1:
    return shared_ptr<zixin>(new xiaoboyao());
    break;
  }
}


int main(int argc, char const *argv[]) {
  shared_ptr<parent> old;
  shared_ptr<parent> old2(old->New(old));
  std::cout << old2->name() << '\n';
  return 0;
}
