#include <iostream>
#include "13_5_StrVec.H"
using namespace std;

StrVec::StrVec(const initializer_list<string> &il)
{
  pair<string*, string*> newdata = alloc_n_copy(il.begin(),il.end());
  elements = newdata.first;
  cap = first_free = newdata.second;
};

StrVec::StrVec(const StrVec &s)
{
  pair<string*, string*> newdata = alloc_n_copy(s.begin(),s.end());
  this->elements = newdata.first;
  this->cap = this->first_free = newdata.second;
};

StrVec& StrVec::operator=(const StrVec &rhs)
{
  pair<string*, string*> newdata = alloc_n_copy(rhs.begin(),rhs.end());
  free();
  this->elements = newdata.first;
  this->cap = this->first_free = newdata.second;
  return *this;
};

// Move constructor and move copy assignment
StrVec::StrVec(StrVec &&obj)
:elements(obj.elements),first_free(obj.first_free),cap(obj.cap)
{
  elements = first_free = cap = nullptr;
};

StrVec &StrVec::operator=(StrVec &&rhs){
  if (this != &rhs) {
    elements = rhs.elements;
    first_free = rhs.first_free;
    cap = rhs.cap;
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
  } else {
    return *this;
  }
};

void StrVec::push_back(const string &s)
{
  check_n_alloc();
  alloc.construct(first_free++, s);
}

void StrVec::push_back(string &&s)
{
  check_n_alloc();
  alloc.construct(first_free++,std::move(s));
};

void StrVec::free()
{
  if (elements) {
    // for(string *p = first_free; p!=elements;)
    // alloc.destroy(--p);
    for_each(elements,first_free,[](string &s){alloc.destroy(&s);});
     alloc.deallocate(elements,cap-elements);

  }
}

void StrVec::reallocate()
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

pair<string*, string*> StrVec::alloc_n_copy(const string *b, const string *e)
{
  string* data = alloc.allocate(e-b); // data point to the first elem
  return {data, uninitialized_copy(b,e,data)};
}

int main(int argc, char const *argv[]) {
  StrVec zixin{"zixin","little_genius","so cute","I love her"};
  // zixin.push_back("zixin");
  // zixin.push_back("little_genius");
  // zixin.push_back("so cute");
  // zixin.push_back("I love her");
  zixin.push_back("I love her so much");
  for(auto value: zixin)
  {
    std::cout << value << '\n';
  }
  return 0;
}
