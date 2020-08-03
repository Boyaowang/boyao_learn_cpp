#include <iostream>
#include <memory>
#include <vector>
#include <memory>
#include <set>

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

  virtual Quote* clone() const & {return new Quote(*this);}
  virtual Quote* clone() const && {return new Quote(std::move(*this));}
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

  virtual Bulk_quote* clone() const & {return new Bulk_quote(*this);}
  virtual Bulk_quote* clone() const && {return new Bulk_quote(std::move(*this));}
};

double print_total(ostream &os, Quote &obj, size_t n)
{
  double ret = obj.net_price(n);
  std::cout << obj.isbn() << " " << ret << '\n';
  return ret;
}

class basket {
public:

  void add_items(const shared_ptr<Quote> &sale)
  {
    items.insert(sale);
  }

  void add_items(const Quote& sale)
  {
    items.insert(shared_ptr<Quote>(sale.clone()));
  }

  void add_items(const Quote&& sale)
  {
    items.insert(shared_ptr<Quote>(std::move(sale).clone()));
  }

  static bool compare(const shared_ptr<Quote> &lhs, const shared_ptr<Quote> &rhs)
  {
    return lhs->isbn() < rhs->isbn();
  };

  double total_receipt(ostream &)const;
private:
  multiset<shared_ptr<Quote>, decltype(compare)*> items{compare}; //bool(*)(Quote &, Quote &

};

double basket::total_receipt(ostream &os) const
{
  double sum = 0.0;
  for (auto it = items.cbegin(); it != items.cend(); it = items.upper_bound(*it)) {
    sum += print_total(os, **it, items.count(*it));
  }
  os << "total sale: " << sum << endl;
  return sum;
};


int main(int argc, char const *argv[]) {
  basket zixin;
  // zixin.add_items(make_shared<Quote>("zixin-1",15.2));
  // zixin.add_items(make_shared<Bulk_quote>("boyao-1",15.1,0.8,0));
  // zixin.total_receipt(cout);
  Quote holmes("holmes",20.2);
  Bulk_quote harry_porter("harry_porter",15.1,0.8,2);
  zixin.add_items(holmes);
  zixin.add_items(holmes);
  zixin.add_items(harry_porter);
  zixin.add_items(harry_porter);
  zixin.add_items(holmes);
  zixin.add_items(harry_porter);
  zixin.total_receipt(cout);
  return 0;
}
