#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class StrBlob {
private:
  shared_ptr<std::vector<string>> data;
public:
  using size_type = std::vector<string>::size_type;
  //constructors and destructor
  StrBlob(){};
  StrBlob(initializer_list<string> il):data(make_shared<std::vector<string>>(il)){};
  virtual ~StrBlob(){};
  //public member functions
  size_type size()const {return data->size();}
  bool empty(){return data->empty();}

  void push_back(string text){data->push_back(text);}
  void pop_back(){data->pop_back();};

  std::string& front(){return data->front();};
  std::string& back(){return data->back();};
  std::string& front()const{return data->front();};
  std::string& back()const{return data->back();};

  void print()const
  {
    for(auto value:*data)
    {
      std::cout << value << '\n';
    }
  }

};

int main(int argc, char const *argv[]) {
  const StrBlob test1({"Zixin","Jiechen","Boyao"});
  StrBlob test2({"zixin","jiechen","boyao"});
  StrBlob test3 = test1;
  test2.back() = "BOYAO";
  test2.print();
  test1.back() ="BOYAO!!!!!";
  test1.print();
  test3.print();
  // std::cout << test1.size() << '\n';
  // std::cout << test2.front() << '\n';
  return 0;
}
