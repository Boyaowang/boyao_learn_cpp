#include <iostream>
#include <vector>
#include <memory>
using namespace std;

template<typename T>
class Blob {
public:
  typedef T value_type;
  //typedef typename std::vector<T>::size_type size_type;
  using size_type = typename std::vector<T>::size_type;
private:
  shared_ptr<std::vector<T>> data;
  void check(size_type i, const string &msg) const;

public:
  template<typename It>
  Blob(It bg, It ed);
  Blob();
  Blob(initializer_list<T> il);
  size_type size(){return data->size();};
  bool empty() const{return data->empty();};
  void push_back(const T&t) {data->push_back(t);};
  void push_back(const T&&t) {data->push_back(std::move(t));};
  void pop_back();
  T& back();
  T& front();
  T& operator[](size_type i);
  virtual ~Blob (){};
};

template<typename T>
void Blob<T>::check(size_type i, const string &msg)const
{
  if (i>=data->size()) {
    throw std::out_of_range(msg);
  }
}

template<typename T>
T& Blob<T>::back()
{
  check(0,"back on empty Blob");
  return data->back();
}

template<typename T>
T& Blob<T>::front()
{
  check(0,"front on empty Blob");
  return data->front();
};

template<typename T>
T& Blob<T>::operator[](size_type i)
{
  check(i, "subscript out of range");
  return (*data)[i];
}

template<typename T>
void Blob<T>::pop_back()
{
  check(0,"pop_back on empty Blob");
  data->pop_back();
}

template<typename T>
template<typename It>
Blob<T>::Blob(It bg, It ed):data(make_shared<std::vector<T>>(bg,ed)){};

template<typename T>
Blob<T>::Blob():data(make_shared<std::vector<T>>()){};

template<typename T>
Blob<T>::Blob(initializer_list<T> il):
                data(make_shared<std::vector<T>>(il)){};

// template<typename T>
// using twin = pair<T,T>;

extern template class Blob<string>;

int main(int argc, char const *argv[]) {
  Blob<string> zixin={"zixin","axin","xiaokeai"};

  return 0;
}
