#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  int a = 0;
  int b =0 ;
  try{
    if (a!=b) {
      throw logic_error("a is not equal to b");
    }
    string error = "equal error";
    if (a == b) {
      throw error;
    }
  }catch(logic_error err){
    std::cout << err.what() << '\n';
  } // try will not terminate the pragram
  catch(string err){
    std::cout << err << '\n';
  }

  std::cout << "*********************************" << '\n';
  if (a!=b) {
    throw runtime_error("a is not equal to b");
  }// This will terminate the pragram

  std::cout << "*********************************" << '\n';
  try{
    if (a!=b) {
      throw runtime_error("a is not equal to b");
    }
  }catch(runtime_error err){
    std::cout << err.what() << '\n';
  }
  return 0;
}
