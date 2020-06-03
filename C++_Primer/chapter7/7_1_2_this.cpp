#include <iostream>
using namespace std;

class sales_items {
private:
   string bookNO;

public:
  sales_items (){};
  virtual ~sales_items (){};
  string isbn()const{return bookNO;};
};

int main(int argc, char const *argv[]) {
   sales_items it1;
  std::cout << it1.isbn() << '\n';
  const sales_items& rit1 = it1;
  const sales_items *pit1 = &it1;
  std::cout << rit1.isbn() << '\n';
  std::cout << pit1->isbn() << '\n';
  return 0;
}
