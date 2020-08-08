#ifndef STRVEC_H_
#define STRVEC_H_
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
using namespace std;


template<typename T>
class StrVec {
private:
  string *elements;
  string *first_free;
  string *cap;
  static allocator<T> alloc;

public:

  StrVec():elements(nullptr),first_free(nullptr),cap(nullptr){};
  StrVec(const initializer_list<T>&);
  StrVec(const StrVec&);
  StrVec& operator=(const StrVec&);
  // Move constructor and move copy assignment
  StrVec(StrVec &&);
  StrVec &operator=(StrVec &&);
  virtual ~StrVec(){free();};

  //member functions
  void push_back(const T&);
  void push_back(T&&);
  size_t size() const{return first_free-elements;};
  size_t capacity()const{return cap-elements;};
  T *begin()const{return this->elements;};
  T *end()const{return this->cap;};
private:
  // private member functions
  void free();
  void reallocate();
  void check_n_alloc(){
    if((*this).size()==(*this).capacity()) reallocate();
  };
  pair<T*, T*> alloc_n_copy(const T*, const T*);

};

template<typename T>
allocator<T> StrVec<T>::alloc;

#endif
