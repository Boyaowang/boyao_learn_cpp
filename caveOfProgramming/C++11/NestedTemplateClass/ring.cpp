#include "ring.h"

template<typename T>
void ring<T>::add(T value){
  arr[arrPos] = value;
  arrPos++;
};
