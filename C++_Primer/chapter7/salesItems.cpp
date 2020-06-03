#include <iostream>
#include "salesItems.h"
//using namespace std;

std::string sales_items::isbn() const
{
    return bookNo;
}

sales_items sales_items::combine(sales_items& rhs){
  this->units_sold += rhs.units_sold;
  return *this;
}
