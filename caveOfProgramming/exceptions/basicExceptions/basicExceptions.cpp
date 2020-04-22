#include <iostream>
using namespace std;

void checkWrong()
{
  bool error = true;
  if (error) {
    throw string("hehe");
  }

  if (error) {
    throw 999;
  }
};

int main(int argc, char const *argv[]) {
  try{
  checkWrong();
}catch(int err)
{std::cout << "error CODE: "<< err << '\n';}
catch(char const* err)//why string does not work
{std::cout << "error CODE: "<< err << '\n';}
catch(string err)//why string does not work
{std::cout << "error CODE: "<< err << '\n';}


  return 0;
}
