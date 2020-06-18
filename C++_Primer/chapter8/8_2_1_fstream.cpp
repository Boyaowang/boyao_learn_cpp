#include <iostream>
#include <fstream>
using namespace std;

class items {
private:
  int amount;
  string bookNo;
  double revenue;

public:
  items (){};
  virtual ~items (){};
  friend istream& read(istream& is, items& obj);
  friend ostream& print(ostream& os, items& obj);
};
istream& read(istream& is, items& obj){
  double price;
  is >> obj.bookNo >> obj.amount >> price;
  obj.revenue = obj.amount * price;
  return is;
}

ostream& print(ostream& os, items& obj){
  os << obj.bookNo << " " << obj.revenue << endl;
}

int main(int argc, char const *argv[]) {
  // int value;
  // string s = "numbers";
  // ifstream in1(s);
  // ifstream in2("numbers");
  // while (in1>>value) {
  //   std::cout << value << '\n';
  // }
  items test;
  ifstream input(argv[1]);
  ofstream output;
  output.open((argv[2]),ofstream::app);
  while (read(input,test)) {
    print(output,test);
  };
  std::cout << *(argv + argc -1) << '\n';
  std::cout << ostream::trunc << '\n';

  return 0;
}
