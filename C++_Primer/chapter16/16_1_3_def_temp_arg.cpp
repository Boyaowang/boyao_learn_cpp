#include <iostream>
using namespace std;

// template<typename T, typename F = less<T> >
// T compare(const T &t1, const T &t2)
// {
//   F f = F();
//   if (f(t1,t2)) {return 1;}
//   if (f(t2,t1)) {return -1;}
//   return 0;
// } is the same as below

template<typename T, typename F = less<T> >
int compare(const T &t1, const T &t2, F f = F())
{
  if (f(t1,t2)) {return 1;}
  if (f(t2,t1)) {return -1;}
  return 0;
}

class forCompare {
private:
  int age;

public:
  forCompare(){};
  forCompare(int age):age(age){};
  virtual ~forCompare (){};
  int yourAge()const
  {
    return age;
  }

};

bool compareAge(const forCompare &obj1, const forCompare &obj2)
{
  if (obj1.yourAge()>obj2.yourAge()) {
    return 1;
  } else {
    return 0;
  }
}

int main(int argc, char const *argv[]) {
  std::cout << compare(8,5) << '\n';
  forCompare item1(1);
  forCompare item2(5);
  //auto a = compare(forCompare(1),forCompare(5),compareAge);
  std::cout << compare(forCompare(1),forCompare(5),compareAge) << '\n';
  return 0;
}
