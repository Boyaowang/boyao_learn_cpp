#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

  std::vector<double> numbers(0);

  int capacity = numbers.capacity();

  std::cout << capacity << '\n';

  for (size_t i = 0; i < 10000; i++) {

    if (numbers.capacity() != capacity) {

      capacity = numbers.capacity();

      std::cout << "The capacity of the vector is " << capacity << '\n';
      std::cout << "The size of the vector is " << numbers.size() << '\n';

    };

    numbers.push_back(i);

  };
  std::cout << "***********vector .resize()****************" << '\n';
  // vector .resize()

  numbers.resize(12);

  std::cout << "The 15 th member of number is " << numbers[15] << '\n';
  std::cout << "The capacity of the vector is " << capacity << '\n';
  std::cout << "The size of the vector is " << numbers.size() << '\n';

  // vector .clear()
  std::cout << "*************vector .clear()**************" << '\n';
  numbers.clear();

  std::cout << "The capacity of the vector is " << capacity << '\n';
  std::cout << "The size of the vector is " << numbers.size() << '\n';

  return 0;
}
