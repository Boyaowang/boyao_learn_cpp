#ifndef SALES_ITEM_H_
#define SALES_ITEM_H_
#include <iostream>

class sales_items {
private:
   std::string bookNo = "unknown";
   unsigned units_sold = 0;
   double revenue = 0.0;
   double bookPrice = 0.0;

public:
  sales_items ()=default;
  sales_items(std::string s){};
  sales_items(std::istream &is){
    read(is,*this);
  };
  virtual ~sales_items (){};

  std::string isbn()const;
  unsigned p_units_sold()const{return units_sold;};
  double p_bookPrice()const{return bookPrice;};
  sales_items combine( sales_items& rhs);

  friend std::istream& read(std::istream& input, sales_items& obj);
  friend inline std::ostream& print(std::ostream& output, sales_items& obj);
  friend sales_items& operator >> (std::istream &is, sales_items &obj);

};

inline std::istream& read(std::istream& input, sales_items& obj){
  double price;
  input >> obj.bookNo >> obj.units_sold >> price;
  obj.revenue = price * obj.units_sold;
  return input;
};

inline std::ostream& print(std::ostream& output, sales_items& obj){
  output << "ISBN:"<< obj.isbn() << " " << "sold:"<<obj.units_sold << " " << "revenue:"<<obj.revenue;
  return output;
}

inline sales_items& operator >> (std::istream &is, sales_items &obj)
{
  is >> obj.bookNo >> obj.units_sold >>obj.bookPrice;
  return obj;
}

#endif
