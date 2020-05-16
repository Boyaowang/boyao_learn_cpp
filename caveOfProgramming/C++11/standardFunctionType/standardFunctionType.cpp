#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

class check {
public:
  check (){};
  virtual ~check (){};
  bool operator()(string name){
    return name.size()==5;
  }
}checkFunctor;

bool checkLength(string name)
{
  return name.size()==5;
}

void run(function<bool(string)> test,std::vector<string> v) //need #include <functional>
{
  std::cout << count_if(v.begin(), v.end(), test) << '\n';
}

int main(int argc, char const *argv[]) {

  std::vector<string> nameList{"boyao","jiechen","zixin"};

  //int count = count_if(nameList.begin(),nameList.end(),checkLength);
  //using lambda
  //int count = count_if(nameList.begin(), nameList.end(), [](string name){return name.size() == 5;});
  int count = count_if(nameList.begin(), nameList.end(), checkFunctor);

  auto checkLengthLambda =[](string name){return name.size() == 5;};

  run(checkLength, nameList);
  run(checkLengthLambda, nameList);
  run(checkFunctor, nameList);

  std::cout << checkFunctor("hhhhh") << '\n';

  //std::cout << count << '\n';

  function<int(int, int)> plus = [](int a, int b){return a+b;};
  std::cout << plus(1,99) << '\n';

  return 0;
}
