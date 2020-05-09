#ifndef RING_H
#define RING_H
#include <iostream>
using namespace std;

template<typename T>
class ring{
private:
  T* arr;
  int arrSize;
  int arrPos;

public:

  ring(int size):arrSize(size),arrPos(0){
    arr = new T[arrSize];
  };
  virtual ~ring(){
    delete [] arr;
  };

public:

  class iterator;

public:

  void add(T value);

  ring& plus(T value)
  {
    arr[arrPos]=value;
    arrPos++;
  }

  void print(){

    for (int i = 0; i < arrSize; i++) {
      std::cout << arr[i] << '\n';
    }
  };

  iterator begin()
  {
    return iterator(0, *this);
  }

  iterator end()
  {
    return iterator(arrSize, *this);
  }
public:
  void testLearn(){
  ring<T>::iterator it = ring::begin();
  std::cout << arr[it.m_pos] << '\n';
  }

};


template<typename T>
class ring<T>::iterator{
private:
  int m_pos;
  ring& m_ring;
public:
  friend class ring;
public:

  iterator(int pos, ring& ringobj):m_pos(pos), m_ring(ringobj){}

  // operator overlaoding
  bool operator!=(const iterator& ringobj){
    return m_pos!=ringobj.m_pos;
  }

  iterator& operator++()
  {
    m_pos++;
  //  return *this;
  }

  iterator& operator++(int)
  {
    m_pos++;
  //  return *this;
  }

  T& operator*()
  {
    return m_ring.arr[m_pos];
  }
  void print();

};

template<typename T>
void ring<T>::iterator::print(){
  for(auto array:arr)
  cout << array << endl;
};

#endif
