#include <iostream>
#include <functional>
#include <memory>
using namespace std;

class friends {
private:
public:
  friends (){};
  virtual ~friends (){};
  virtual void friendsSpeak()
  {
    std::cout << "we are your friends" << '\n';
  }
  virtual void Property()
  {
    std::cout << "friends can be animal or people" << '\n';
  }
};

class families {
private:
public:
  families (){};
  virtual ~families (){};
  virtual void familiesSpeak(){
    std::cout << "we are you relatives" << '\n';
  }
  virtual void Property()
  {
    std::cout << "families can also be animals or people" << '\n';
  }
};

class people: public friends, public families {
private:
public:
  people (){
  //  std::cout << "make" << '\n';
  };
  virtual ~people (){
  //  std::cout << "destroy" << '\n';
  };
};

int main(int argc, char const *argv[]) {
/*
  people* boyao = new people();
  delete boyao;

  {unique_ptr<people> boyao2(new people);}
  std::cout << "finished" << '\n';
  //auto_ptr<people> boyao3(new people);
*/
  unique_ptr<people> test(new people);
  test->friendsSpeak();
  test->familiesSpeak();
  test->friends::Property();
  test->families::Property();

  return 0;
}
