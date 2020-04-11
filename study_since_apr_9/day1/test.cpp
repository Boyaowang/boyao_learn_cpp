template<class T>
struct A;
template<class T>
using B = typename A<T>::U; // type-id is A<T>::U
template<class T>
struct A { typedef B<T> U; };


int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
