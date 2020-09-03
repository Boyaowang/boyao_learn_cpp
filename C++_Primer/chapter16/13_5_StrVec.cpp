#include <iostream>
#include "13_5_StrVec.H"
using namespace std;

template<typename T>
StrVec<T>::StrVec(const initializer_list<T> &il)
{
  pair<T*, T*> newdata = alloc_n_copy(il.begin(),il.end());
  elements = newdata.first;
  cap = first_free = newdata.second;
};

template<typename T>
StrVec<T>::StrVec(const StrVec &s)
{
  pair<T*, T*> newdata = alloc_n_copy(s.begin(),s.end());
  this->elements = newdata.first;
  this->cap = this->first_free = newdata.second;
};

template<typename T>
StrVec<T>& StrVec<T>::operator=(const StrVec &rhs)
{
  pair<T*, T*> newdata = alloc_n_copy(rhs.begin(),rhs.end());
  free();
  this->elements = newdata.first;
  this->cap = this->first_free = newdata.second;
  return *this;
};

// Move constructor and move copy assignment
template<typename T>
StrVec<T>::StrVec(StrVec &&obj)
:elements(obj.elements),first_free(obj.first_free),cap(obj.cap)
{
  elements = first_free = cap = nullptr;
};

template<typename T>
StrVec<T> &StrVec<T>::operator=(StrVec &&rhs){
  if (this != &rhs) {
    elements = rhs.elements;
    first_free = rhs.first_free;
    cap = rhs.cap;
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
  } else {
    return *this;
  }
};

template<typename T>
void StrVec<T>::push_back(const T &s)
{
  check_n_alloc();
  alloc.construct(first_free++, s);
}

template<typename T>
void StrVec<T>::push_back(T &&s)
{
  check_n_alloc();
  alloc.construct(first_free++,std::move(s));
};

template<typename T>
void StrVec<T>::free()
{
  if (elements) {
    // for(T *p = first_free; p!=elements;)
    // alloc.destroy(--p);
    for_each(elements,first_free,[](T &s){alloc.destroy(&s);});
     alloc.deallocate(elements,cap-elements);

  }
}

template<typename T>
void StrVec<T>::reallocate()
{
  size_t newcap = (*this).size()? 2*(*this).size():1;
  auto newdata = alloc.allocate(newcap);
  auto dest = newdata;
  auto elem = this->elements;
  for (size_t i = 0; i !=this->size(); i++) {
    alloc.construct(dest++, move(*elem++));
  }
  free();
  this->elements = newdata;
  this->first_free = dest;
  this->cap = elements + newcap;
  std::cout << "call reallocate " << this->size() << '\n';
}

template<typename T>
pair<T*, T*> StrVec<T>::alloc_n_copy(const T *b, const T *e)
{
  T* data = alloc.allocate(e-b); // data point to the first elem
  return {data, uninitialized_copy(b,e,data)};
}

int main(int argc, char const *argv[]) {
   StrVec<string> zixin{"zixin","little_genius","so cute","I love her"};
  // // zixin.push_back("zixin");
  // // zixin.push_back("little_genius");
  // // zixin.push_back("so cute");
  // // zixin.push_back("I love her");
  // zixin.push_back("I love her so much");
  for(auto value: zixin)
  {
    std::cout << value << '\n';
  }
  return 0;
}