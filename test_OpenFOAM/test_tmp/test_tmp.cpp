#include <iostream>
using namespace std;

namespace Foam
{
  template<typename T>
  class test_tmp {
  private:
    T* tmp_mem;

  public:
    test_tmp (T* a):tmp_mem(a){};
    virtual ~test_tmp (){};
      void operator++();
      void call_refprint()
      {
        tmp_mem->print();
      }
  };
/////////////////////////////////////////
  class test_refcount {
  private:
    int ref_count = 0;

  public:
    test_refcount (){};
    virtual ~test_refcount (){};
    void operator++() {
      ref_count++;
      std::cout << "/* message */" << '\n';
    }
    void print()
    {
      if (ref_count<1) {
        std::cout << "to be deleted" << '\n';
      }else{
        std::cout << "keep it" << '\n';
        std::cout << "the count is "<< ref_count << '\n';
      }
    }
  };

}

template<typename T>
void Foam::test_tmp<T>::operator++()
{
  tmp_mem->operator++();
  tmp_mem->print();
}
///////////////////////////////////////////////////////////////
class input :public Foam::test_refcount
{
private:
  std::string name;
public:
  input (string name):name(name){};
  input(){};
  virtual ~input (){};
};
//////////////////////////////////////////////////////////////////

using namespace Foam;

int main(int argc, char const *argv[]) {
  input axin("zixin");
  input* test = &axin;
  test_tmp<input> zixin(test);
  ++zixin;
  //
  // int a = 999;
  // int *pa = &a;
  // test_tmp<int> zixin2(pa);
  // ++zixin2;

  zixin.operator++();
  zixin.call_refprint();


  return 0;
}
// Tell myselft:
// T must be inherited from refcount, a tmp<> object cannot be built. It might
// be hard to find where it is inherited, but you will find it!
