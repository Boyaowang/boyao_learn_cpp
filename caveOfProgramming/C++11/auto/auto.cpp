#include <iostream>
using namespace std;

template<class T>
class people {
private:
  T name;
public:
  people (T name):name(name){};
  virtual ~people (){};

  auto print() ->decltype(name)
  {
    std::cout << name << '\n';
  }
};

template<class T1, class T2>
auto returnPlus(T1 value1, T2 value2)-> decltype(value1+value2)
{
  return value1+value2;
}

int get()
{return 999;}

auto printGet()->decltype(get())
{
  std::cout << get() << '\n';
}

int main(int argc, char const *argv[]) {

  people<string> boyao("Boyao");
  boyao.print();

  std::cout << returnPlus(8,13) << '\n';
  printGet();

  return 0;
}
