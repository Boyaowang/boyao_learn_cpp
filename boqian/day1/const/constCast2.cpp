#include <iostream>
using namespace std;

int fun(int* ptr)
{
	return (*ptr + 10);
}

int fun2(int* ptr)
{
  *ptr += 10;
}

int main(void)
{
	int val = 10;
	const int *ptr = &val;
	int *ptr1 = const_cast <int *>(ptr);
	cout << fun(ptr1)<< endl;
  fun2(ptr1);
  std::cout << val << '\n';
  std::cout << typeid(val).name() << '\n';
	return 0;
}
