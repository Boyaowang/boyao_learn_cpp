#include <iostream>
#include <memory>
#include <fstream>

using namespace std;

void use_allocator(size_t n, string fileName="girlFriend") {

  ifstream myLove(fileName);

  allocator<string> alloc;
  auto const p = alloc.allocate(n);
  auto q = p;
  string nickName;
  while (q!=p+n && getline(myLove,nickName)) {
    //*q = nickName;
    alloc.construct(q++,nickName);
  }

  while (q != p){
    std::cout << *--q << " ";
    alloc.destroy(q);
  }
  alloc.deallocate(p, n);
}

int main(int argc, char const *argv[]) {
  use_allocator(5);
  return 0;
}
