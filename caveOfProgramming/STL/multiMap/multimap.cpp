#include <iostream>
#include <map>

using namespace std;

int main(int argc, char const *argv[]) {

  multimap<int, string> people;
  pair<int, string> boyao(25,"boyao");
  pair<int, string> jiechen(26,"jiechen");
  pair<int, string> jianbiao(25,"jianbiao");
  pair<int, string> zixin(24,"zixin");

  people.insert(boyao);
  people.insert(jiechen);
  people.insert(jianbiao);
  people.insert(zixin);

  for (multimap<int,string>::iterator it = people.begin(); it != people.end(); it++) {
    std::cout << it->first << " "<< it->second << '\n';
  }

  std::cout << "-------------------------" << '\n';

  for (multimap<int,string>::iterator it = people.find(25); it != people.end(); it++) {
    std::cout << it->first << " "<< it->second << '\n';
  }

  multimap<string, int> people2;
  //pair<string, int> boyao2("boyao",25);
  people2.insert(make_pair("boyao",25));
  pair<string, int> jiechen2("jiechen",26);
  //  std::cout << jiechen2.first << '\n';
  pair<string, int> jianbiao2("jianbiao",25);
  pair<string, int> zixin2("zixin",25);

  //people2.insert(boyao2);
  people2.insert(jiechen2);
  people2.insert(jianbiao2);
  people2.insert(zixin2);

  for (multimap<string,int>::iterator it = people2.begin(); it != people2.end(); it++) {
    std::cout << it->first << " "<< it->second << '\n';
  }

  std::cout << "-------------------------" << '\n';

  for (multimap<string,int>::iterator it = people2.find("jiechen"); it != people2.end(); it++) {
    std::cout << it->first << " "<< it->second << '\n';
  }

  //pair<multimap<int,string>::iterator,multimap<int,string>::iterator> itPair = people.equal_range(25);
  auto itPair = people.equal_range(25); // auto which is new in C++ 11 is fantastic....
  std::cout << "-------------------" << '\n';
  for (multimap<int,string>::iterator it = itPair.first; it != itPair.second; it++) {
    std::cout << it->first << " "<< it->second << '\n';
  }


  return 0;
}
