#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
  string number{"0123456789"};
  string abracdabra{"hd9824390ncnnqwoe"};

  string::size_type pos = 0;
  while ((pos = abracdabra.find_first_of(number,pos))!=string::npos) {
    std::cout << "The pos is " << pos << " The value is " <<abracdabra[pos] << '\n';
    pos ++;
  }
  return 0;
}
