#include <iostream>
using namespace std;

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

  friend class boyao;
};


class boyao
{
public:
  void tellIamfriend(jiechen& obj)
  {
    obj.myfriendname = "boyao";
  };
};


/*
void boyao::tellIamfriend(jiechen &obj)
{
  obj.myfriendname = "boyao";
};
*/


int main(int argc, char const *argv[]) {
  jiechen Jiechen;
  boyao Boyao;
  Boyao.tellIamfriend(Jiechen);
  Jiechen.printmyfriendname();
  return 0;
}
