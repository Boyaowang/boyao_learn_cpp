#include <iostream>
#include <set>

using namespace std;

class Person
{
private:
  int age;
  string name;
public:
  //Person(){};
  Person(int age, string name): name(name), age(age){};
  void print() const
  {
    std::cout << name << " "<< age << '\n';
  }

  bool operator < (const Person& obj) const
  {
    if (name!=obj.name) {
      return name < obj.name;
    } else {
      return age < obj.age;
    }
  };

};
int main(int argc, char const *argv[]) {
  set<int> age;
  age.insert(10);
  age.insert(11);
  age.insert(12);
  age.insert(13);

  for (set<int>::iterator it = age.begin(); it != age.end(); it++) {
    std::cout << *it << '\n';
  }

  set<int>::iterator itFind = age.find(12);
  if (itFind != age.end()) {
    std::cout << "*****************" << '\n';
    std::cout << *itFind << '\n';
  };
  // count return 0 or 1
  if (age.count(12)) {
    std::cout << "number found" << '\n';
  }
  // set<class>

  set<Person> myFriends;
  myFriends.insert(Person(26,"jiechen"));
  myFriends.insert(Person(666,"jiechen"));
  myFriends.insert(Person(25,"jianbiao"));
  myFriends.insert(Person(24,"zixin"));
  myFriends.insert(Person(25,"boyao"));
  myFriends.insert(Person(28,"zhongwei"));

  std::cout << "They are my friends: " << '\n';
  for (set<Person>::iterator it = myFriends.begin(); it != myFriends.end(); it++) {
    it->print();
  }



  return 0;
}
