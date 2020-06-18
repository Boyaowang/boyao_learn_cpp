#include <iostream>
#include "salesItems.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
using namespace std;

bool compareISBN(sales_items&s1, sales_items&s2)
{
  return s2.isbn() < s1.isbn();
}

int main(int argc, char const *argv[]) {
  ifstream books("books");
  istream_iterator<sales_items> in(books),eof;
  std::vector<sales_items> v_item{in,eof};
  sort(v_item.begin(),v_item.end(),compareISBN);
  for(auto obj : v_item)
  {
    std::cout << obj.isbn() << " " << obj.p_units_sold() <<" " << obj.p_bookPrice() << '\n';
  }
  return 0;
}
