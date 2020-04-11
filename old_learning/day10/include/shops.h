#include <iostream>
using namespace std;

#ifndef SHOPS_H_
#define SHOPS_H_

namespace shops{

namespace shop1{
  class dogs{
  public:
    dogs();
    void dogspeak();
  };
  class cats{
  public:
    cats();
    void catspeak();
  };
};

namespace shop2{
  class dogs{
  public:
    dogs();
    void dogspeak();
  };
  class cats{
  public:
    cats();
    void catspeak();
  };
}
namespace Parray
{
  class parray{
  private:
    int n;
  public:
    parray(){
      std::cout << "How many dogs do you want?" << '\n';
      std::cin >> n;
    }
    int* parr(){
      int* arr=new int[n];
      return arr;
    }
    int* arrloop(int* arr)
    {
      for (int i = 0; i < n; i++) {
        arr[i]=i+1;
      }
      for (int i = 0; i < n; i++) {
        std::cout << arr[i] << '\n';
      }
    }
    void rmem(int* arr){
      delete [] arr;
    }
  };
}
}
#endif
