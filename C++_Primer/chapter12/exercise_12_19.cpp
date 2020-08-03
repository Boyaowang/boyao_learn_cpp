#include <iostream>
#include <vector>
#include <memory>
#include <fstream>

using namespace std;
// forward declaratio of StrBlobPtr
class StrBlobPtr;
class StrBlob {
public:
  friend class StrBlobPtr;
private:
  shared_ptr<std::vector<string>> data;
public:
  using size_type = std::vector<string>::size_type;
  //constructors and destructor
  StrBlob():data(make_shared<std::vector<string>>()){};
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

  StrBlobPtr begin();
  StrBlobPtr end();

};

class StrBlobPtr {
private:
  weak_ptr<std::vector<string>> wptr;
  size_t curr;
public:
  StrBlobPtr():curr(0){};
  StrBlobPtr(StrBlob &a, size_t sz=0):wptr(a.data),curr(sz){};

  string &deref()const{
    auto p = wptr.lock();
    return (*p)[curr];
  };

  StrBlobPtr &incr(){
    curr++;
    return *this;
  };

  size_t Curr(){return curr;}

  virtual ~StrBlobPtr (){};
};

StrBlobPtr StrBlob::begin(){return StrBlobPtr(*this);};
StrBlobPtr StrBlob::end(){return StrBlobPtr(*this,data->size());};


int main(int argc, char const *argv[]) {
  ifstream girlFriend("girlFriend");
  StrBlob myLove;
  string nickName;
  while (girlFriend>>nickName) {
    myLove.push_back(nickName);
  }
  for(StrBlobPtr it = myLove.begin();it.Curr()!=myLove.end().Curr();it.incr())
  {
    std::cout << it.deref() << '\n';
  };

  return 0;

}
