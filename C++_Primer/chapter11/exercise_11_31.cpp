#include <map>
#include <string>
#include <iostream>

using namespace std;

int main() {
  std::multimap<std::string, std::string> authors;

  authors.insert({"Zhang San", "Hello world 3"});
  authors.insert({"Zhang San", "Hello world"});
  authors.insert({"Wang Wu", "Hello again world 2"});
  authors.insert({"Zhang San", "Hello world 2"});
  authors.insert({"Li Si", "Bye world"});
  authors.insert({"Wang Wu", "Hello again world"});

  string name = "Zhang San";
  auto it = authors.find(name);
  if (it != authors.end()) {
      std::cout << it->first << '\n';
       authors.erase(it->first);

    } else {
      std::cout << name << " is not find." << '\n';
    }


  // for(auto names : authors)
  // {
  //   for(auto pos = authors.equal_range(names.first);pos.first!=pos.second;++pos.first)
  //   {
  //     std::cout << "author: " << names.first << " " << pos.first->second << '\n';
  //   }
  // }
  for(auto authornames : authors)
  {
    std::cout << authornames.first << " "<<authornames.second << '\n';
  }

  return 0;

}
