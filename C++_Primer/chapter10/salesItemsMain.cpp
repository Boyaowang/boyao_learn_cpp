#include <iostream>
#include "salesItems.h"
using namespace std;

int main(int argc, char const *argv[]) {
  sales_items total;
  if (read(cin,total)) {
    sales_items trans;
    while (read(cin,trans)) {
      if (total.isbn() == trans.isbn()) {
        total.combine(trans);
      }else{
        print(cout,total) << endl;
        total = trans;
      }
    }
    print(cout,total);
  }else{
    std::cerr << "/* error message */" << '\n';
  }

  // sales_items total2;
  // //print(cout,total2) << '\n';
  // string s = "7878";
  // total2.combine(s);
  return 0;
}
