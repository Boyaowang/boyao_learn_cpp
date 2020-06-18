#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
using namespace std;

void insert_id(forward_list<string> &list, string name, string id) {
    auto it = list.before_begin();
    auto it2 = list.begin();
  while (it2!= list.end()) {
    if (*it2 == name) {
      it = list.insert_after(it2,id);
      it2++;
    }
    else {
      it = it2;
      it2++;
    }
  }
  list.insert_after(it,"\nno strawberry is found");
}
int main(int argc, char const *argv[]) {
  forward_list<string> fls{"boyao","zixin","jiechen",};
  string name = "zixin";
  string identity = "is strawberry";

  insert_id(fls,name,identity);
  for(auto value: fls)
  {
    std::cout << value << " ";
  }


  return 0;
}
