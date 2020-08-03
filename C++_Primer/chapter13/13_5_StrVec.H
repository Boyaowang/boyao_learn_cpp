#ifndef STRVEC_H_
#define STRVEC_H_
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
using namespace std;

class StrVec {
private:
  string *elements;
  string *first_free;
  string *cap;
  static allocator<string> alloc;

public:

  StrVec():elements(nullptr),first_free(nullptr),cap(nullptr){};
  StrVec(const initializer_list<string>&);
  StrVec(const StrVec&);
  StrVec& operator=(const StrVec&);
  // Move constructor and move copy assignment
  StrVec(StrVec &&);
  StrVec &operator=(StrVec &&);
  virtual ~StrVec(){free();};

  //member functions
  void push_back(const string&);
  void push_back(string&&);
  size_t size() const{return first_free-elements;};
  size_t capacity()const{return cap-elements;};
  string *begin()const{return this->elements;};
  string *end()const{return this->cap;};
private:
  // private member functions
  void free();
  void reallocate();
  void check_n_alloc(){
    if((*this).size()==(*this).capacity()) reallocate();
  };
  pair<string*, string*> alloc_n_copy(const string*, const string*);

};

allocator<string> StrVec::alloc;

#endif
