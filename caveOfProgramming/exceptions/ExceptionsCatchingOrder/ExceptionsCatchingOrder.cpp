#include <iostream>
#include <exception>
using namespace std;

void goesWrong()
{
  bool error1= false;
  bool error2= true;
   if (error1) {
     throw bad_alloc();
   };
   if (error2) {
     throw exception();
   };
};
// Remember bad_alloc is a sub-class of exception
int main(int argc, char const *argv[]) {
  try{
    goesWrong();
  }catch(bad_alloc& e)
  {
    std::cout << "Bad_alloc: "<< e.what() << '\n';
  }catch(exception& e)
  {
    std::cout << "exception: "<< e.what() << '\n';
  }
  return 0;
}
