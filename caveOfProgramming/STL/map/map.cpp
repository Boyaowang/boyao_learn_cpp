#include <iostream>
#include <map>

using namespace std;

int main(int argc, char const *argv[]) {
  //Just imagine string could be a name and int could be an age
  map<string, int> ages;

  ages["jiechen"] = 26;
  ages["boyao"] = 25;
  ages["zixin"] = 25;

  // insert to map
  /*
  pair<string, int> insertToMap("peter", 15);

  ages.insert(insertToMap);

  std::cout << ages["zixin"] << '\n';
  */

  // Or insert like this
  /*
  ages.insert(pair<string,int>("peter", 15) );
 */


// Or even advanced using make_pair()
  ages.insert(make_pair("peter",15));


// show what is in the map
  for (std::map<string, int>::iterator it = ages.begin(); it != ages.end(); it++) {
    std::cout << it->first << ' '; // name here
    std::cout << it->second << '\n'; // age here
  }

// the key is always unique
  ages["zixin"] = 24;
  for (std::map<string, int>::iterator it = ages.begin(); it != ages.end(); it++) {
    std::cout << it->first << ' '; // name here
    std::cout << it->second << '\n'; // age here
  }
// use the find method
  if (ages.find("Boyao")!=ages.end()){  // try to find the key
    std::cout << "The key is fond" << '\n';
  }
  else
  {
    std::cout << "The key is not found" << '\n';
  }

  for (std::map<string, int>::iterator it = ages.begin(); it != ages.end(); it++) {
    std::cout << it->first << ' '; // name here
    std::cout << it->second << '\n'; // age here
  }
  return 0;
}
