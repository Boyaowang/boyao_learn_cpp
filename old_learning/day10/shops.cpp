#include <iostream>
#include "shops.h"

using namespace std;

namespace shops{
namespace shop1{
  // dogs class
    dogs::dogs()
    {
      std::cout << "Do you like wangwang?" << '\n';
    };
    void dogs::dogspeak()
    {
      std::cout << "woooooo!!" << '\n';
    };
    //cats class
    cats::cats(){
      std::cout << "Do you like mimi?" << '\n';
    };
    void cats::catspeak()
    {
      std::cout << "miao!!" << '\n';
    };
  };

namespace shop2{
    // dogs class
    dogs::dogs(){
      std::cout << "your royal friend!" << '\n';
    };
    void dogs::dogspeak()
    {
      std::cout << "ohwwwww!!!" << '\n';
    };
    // cats class
    cats::cats()
    {
      std::cout << "I am always with you!" << '\n';
    };
    void cats::catspeak()
    {std::cout << "sssss!!" << '\n';};
}

};
