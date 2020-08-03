#include <iostream>
#include <memory>
#include <vector>
#include <memory>

using namespace std;

class Quote{
private:
  string ISBN = "unknown";
protected:
  double price = 0.0;
public:
  Quote() = default;
  Quote(string ISBN, double price):ISBN(ISBN),price(price){};
  virtual ~Quote (){};

  virtual string isbn()const{return ISBN;};
  virtual double net_price(size_t n) const{
    std::cout << "Quote" << '\n';
    return n*price;
  };
  virtual void debug(/* arguments */);
};

void Quote::debug() {
  std::cout << "The members in Quote class" << '\n';
  std::cout << "ISBN: " << ISBN << '\n';
  std::cout << "price: " << price << '\n';
}

class Disc_quote:public Quote{
protected:
  size_t quantity = 0;
  double discount = 0.0;

public:
  Disc_quote ()=default;
  Disc_quote(string ISBN, double price, double disc,size_t min_qty):Quote(ISBN,price),discount(disc),quantity(min_qty){
  };
  virtual ~Disc_quote (){};

  virtual double net_price(size_t n) const = 0; // a pure virtual function

};


class Bulk_quote:public Disc_quote{
private:
   //double discount;
   //size_t min_qty = 0;
public:
  Bulk_quote()=default;
  //Bulk_quote(string ISBN, double price):ISBN(ISBN),price(price){};
  //using Disc_quote::Disc_quote;
  //same as

  Bulk_quote(string ISBN, double price, double disc,size_t min_qty):Disc_quote(ISBN,price,disc,min_qty){};

  virtual ~Bulk_quote(){};
  //string isbn()const{return ISBN;};

  double net_price(size_t n) const override{
    //std::cout << "bulk version...." << '\n';

    if (n>=quantity) {
      return n*price*discount;

    }
    return n*price;
  };
};

void print_total(ostream &os, Quote &obj, size_t n)
{
  double ret = obj.net_price(n);
  std::cout << obj.isbn() << " " << ret << '\n';
}

// class test:private Quote {
// private:
//   /* data */
//
// public:
//   Quote::price;
//   test (){};
//   virtual ~test (){};
//   void print_price(/* arguments */) {
//     std::cout << price << '\n';
//   }
// };

int main(int argc, char const *argv[]) {
  // Quote boyao("999-000-111", 12.5);
  // Bulk_quote zixin("000-111-999", 15.2,0.8,1);
   // print_total(cout,zixin,2);
  // Quote *zixin2 = &zixin;
  // zixin2->net_price(3);
  // zixin2->Quote::net_price(3);
  // zixin2->debug();
  // test xiaoboyao;
  // std::cout << xiaoboyao.price << '\n';
  //
  // Bulk_quote boyaowby;

  // Bulk_quote xiaoboyao("000-111-999", 15.2,0.8,1);
  // Quote *zixin = &xiaoboyao;
  // std::cout << zixin.net_price(2) << '\n';
  std::vector<shared_ptr<Quote>> books;
  books.push_back(make_shared<Quote>("999-000-111", 12.5));
  books.push_back(make_shared<Bulk_quote>("000-111-999", 15.2,0.8,1));
  //std::cout << books[1]->net_price(10) << '\n';
  for(auto obj:books)
  {
    std::cout << obj->net_price(2) << '\n';
  }
  return 0;
}
