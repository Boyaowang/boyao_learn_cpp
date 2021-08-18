#include <matrix2.h>
// #include <iostream>
// #include <type_traits>
// #include <typeinfo>
// #include <memory>
// #ifndef _MSC_VER
// #   include <cxxabi.h>
// #endif
// #include <string>
// #include <cstdlib>

//C language
// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include <time.h>
// #include <string.h>

#define FINE_PARTICLE_MESH 5

// typedef	struct	{
// 		int	dim, max_dim;
// 		double *ve;
// 		} VEC;

extern	VEC *v_get();
extern	VEC *v_get(int);
// extern VEC *v_get2(10);
/* v_get -- gets a VEC of dimension 'size'
   -- Note: initialized to zero */
#ifndef ANSI_C
VEC	*v_get(size)
int	size;
#else
VEC	*v_get(int size)
#endif
{
   VEC	*vector;

   vector->dim = size;

   return (vector);
}


void discretized_psm()
{
	VEC *b, *T;
	b=v_get(FINE_PARTICLE_MESH);
}


// template <class T>
// std::string
// type_name()
// {
//   typedef typename std::remove_reference<T>::type TR;
//   std::unique_ptr<char, void(*)(void*)> own
//   (
//     #ifndef _MSC_VER
//     abi::__cxa_demangle(typeid(TR).name(), nullptr,
//     nullptr, nullptr),
//     #else
//     nullptr,
//     #endif
//     std::free
//   );
//   std::string r = own != nullptr ? own.get() : typeid(TR).name();
//   if (std::is_const<TR>::value)
//   r += " const";
//   if (std::is_volatile<TR>::value)
//   r += " volatile";
//   if (std::is_lvalue_reference<T>::value)
//   r += "&";
//   else if (std::is_rvalue_reference<T>::value)
//   r += "&&";
//   return r;
// }
// VEC *v_get(int a)
// {
//   std::cout << "/* message */" << '\n';
// };

int main(void) {
  // using PF = VEC* (int);
  // PF b;

  VEC *c;
  int size = 50;
	discretized_psm();
  // c=v_get(size);
  // //
  // //
  // // std::cout << b.dim << '\n';
  // // // VEC a={1,2};
  // // printf("%d", v_get);
  // std::cout << typeid(v_get).name() << '\n';
  // std::cout << typeid(b).name() << '\n';
  // const int ci = 0;
  // std::cout << type_name<decltype(v_get)>() << '\n';
  // std::cout << type_name<decltype(b)>() << '\n';
  return 0;
}
