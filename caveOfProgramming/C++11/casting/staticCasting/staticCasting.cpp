#include <iostream>
using namespace std;

class friends {
private:
  /* data */

public:
  friends (){};
  virtual ~friends (){};
  void print()
  {
    std::cout << "/* message */" << '\n';
  }
};

class boys:public friends {
private:
  /* data */

public:
  boys (){};
  virtual ~boys (){};

};

class girls:public friends {
private:
  /* data */

public:
  girls (){};
  virtual ~girls (){};
};

void testMeaning(friends* obj)
{
  if (obj == nullptr) {
    std::cout << "meaningless" << '\n';
    std::cout << obj << "nullptr" << '\n';
  }else
  {
    std::cout << obj << '\n';
  }
}

int main(int argc, char const *argv[]) {

  double value = 99.99;
  std::cout << (int)value << '\n'; // old cast method
  std::cout <<  int(value) << '\n';  // old cast method

  std::cout << static_cast<int>(value) << '\n'; // in C++

  friends myFriends;
  boys boyFriends;
  boys* pBoyFriendsInit;
  girls girlFriends;

  friends *pBoyFriends = &boyFriends;
  boys *pFriends = static_cast<boys*>(&myFriends);

  //friends&& rFriends = friends();
  friends&& rFriends = static_cast<friends&& >(myFriends);
  rFriends.print();

  boys *pFriends2 = dynamic_cast<boys*>(&myFriends);

  girls *pGirlFriends = dynamic_cast<girls*>(&boyFriends);
  girls *pGirlFriends2 = reinterpret_cast<girls*>(&boyFriends);




  testMeaning(pFriends);
  testMeaning(pFriends2);
  testMeaning(pGirlFriends);
  testMeaning(pGirlFriends2);



  //friends* lfriends = myFriends;



  return 0;
}
