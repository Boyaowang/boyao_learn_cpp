#include <iostream>

class name {
public:
  typedef std::string STRING;

public:
  name (){};
  virtual ~name (){};
};

template<typename T>
typename T::STRING return_name(typename T::STRING name)
{
  return name;
}

int main(int argc, char const *argv[]) {
  std::cout << return_name<name>("axin") << '\n';
  return 0;
}
