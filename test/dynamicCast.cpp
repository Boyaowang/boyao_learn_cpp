#include <iostream>
using namespace std;

class base0 {
private:
  /* data */

public:
  base0 (){};
  // void printName(/* arguments */) {
  //   std::cout << "/* message */" << '\n';
  // }
  virtual ~base0 (){};
};

class base {
private:
  /* data */

public:
  base (){};
  virtual ~base (){};
};

class child1 : public base {
private:
  /* data */

public:
  child1 (){};
  virtual ~child1 (){};
};

class child2 : public base, public base0 {
private:
  /* data */

public:
  child2 (){};
  virtual ~child2 (){};
};

int main(int argc, char const *argv[]) {

  child1 boyao;
  base0& a = dynamic_cast<base0&>(boyao);
  //a.printName();
  return 0;
}
