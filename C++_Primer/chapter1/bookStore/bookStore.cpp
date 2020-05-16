#include <iostream>
using namespace std;

class Sales_item {
private:
  string ISBN;
  double price;
  double revenue;

public:
  Sales_item (){};
  virtual ~Sales_item (){};
  friend istream& operator>>(istream& input, Sales_item& obj);
  friend ostream& operator<<(ostream& output, Sales_item& obj);

  string isbn()
  {
    return ISBN;
  }

  Sales_item operator+=(const Sales_item& obj){
    this->revenue += obj.price;
    return *this;
  }

  Sales_item operator+(const Sales_item& obj){
    this->revenue += obj.price;
    return *this;
  }
};

 istream& operator>>(istream& input, Sales_item& obj){
      //std::cout << "input a ISBN" << '\n';
      input >> obj.ISBN >> obj.price;
      obj.revenue = obj.price;
      return input;
  };

  ostream& operator<<(ostream& output, Sales_item& obj){
       output << "your ISBN is "<< obj.ISBN << "\n"
       //<<"The price is " << obj.price << "\n"
       <<"The revenue is " << obj.revenue << endl;
       return output;
  };

  class baba {
  private:
    /* data */

  public:
    int age=10;
    baba (){};
    virtual ~baba (){};

  };

    ostream& operator<<(ostream& out, baba rhs)
    {
      out << rhs.age <<endl;
      return out;
    }




int main(int argc, char const *argv[]) {
  //Sales_item book;
  /*while (std::cin >> book) {
    std::cout << book << '\n';
  };*/
  /*
  Sales_item total;
  if (std::cin >> total) {
    Sales_item trans;
    while (std::cin >> trans) {
      if (total.isbn() == trans.isbn()) {
        total+=trans;
        //std::cout << total << '\n';
      } else {
        std::cout << total << '\n';
        total = trans;
      }
    }
    std::cout << total << '\n';
  }
  */

  baba father;
  std::cout << father << '\n';


  return 0;
}
