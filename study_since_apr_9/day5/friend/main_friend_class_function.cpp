#include <iostream>
using namespace std;

class jiechen;

class boyao
{
public:
  void tellIamfriend(jiechen &obj);
};

class jiechen
{
private:
  string myfriendname;
public:
  jiechen()
  :myfriendname("unknown..")
  {};
  void printmyfriendname()
  {
    std::cout << "My friend's name is "<< myfriendname << '\n';
  };

  friend void boyao::tellIamfriend(jiechen &obj);
};


void boyao::tellIamfriend(jiechen &obj)
{
  obj.myfriendname = "boyao";
};



int main(int argc, char const *argv[]) {
  jiechen Jiechen;
  boyao Boyao;
  Boyao.tellIamfriend(Jiechen);
  Jiechen.printmyfriendname();
  return 0;
}
