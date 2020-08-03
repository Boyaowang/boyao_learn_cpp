#include <iostream>
#include <map>
#include <fstream>
#include <set>
#include "salesItems.h"

using namespace std;

bool compareISBN(sales_items &s1, sales_items &s2)
{
  return s1.isbn() < s2.isbn();
}

int main(int argc, char const *argv[]) {
  std::set<sales_items,bool(*)(sales_items&, sales_items&)> salesItems_set(compareISBN);
  return 0;
}
