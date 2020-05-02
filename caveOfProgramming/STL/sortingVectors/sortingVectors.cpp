#include <iostream>
#include <vector>
#include <algorithm> // for sort

using namespace std;

class Person {
private:
  int age;
  string name;

public:
  Person(string name, int age):name(name), age(age){};

  void print() {
    std::cout << name << " " << age << '\n';
  }
/*
  bool operator < (Person& obj)
  {
    if (name!=obj.name) {
      return name<obj.name;
    } else {
      return age < obj.age;
    }
  }
*/
  friend bool comp(Person& person1, Person& person2);// a friend function
  virtual ~Person(){};
};

bool comp(Person& person1, Person& person2)
{
  if (person1.name!=person2.name) {
    return person1.name<person2.name;
  } else {
    return person1.age < person2.age;
  }
};
int main(int argc, char const *argv[]) {
  std::vector<Person> person;

  person.push_back(Person("zhongwei", 29));
  person.push_back(Person("zixin", 24));
  person.push_back(Person("jiechen", 26));
  person.push_back(Person("jianbiao", 25));

  std::cout << "*****before sorting*****" << '\n';
  for (std::vector<Person>::iterator it = person.begin(); it != person.end(); it++) {
    it->print();
  }

  //sort(person.begin(),person.end());// from the begin of the vector to its end

  sort(person.begin(),person.end()-1,comp);// comp is a function pointer
  std::cout << "*****after sorting*****" << '\n';
  for (std::vector<Person>::iterator it = person.begin(); it != person.end(); it++) {
    it->print();
  }




  return 0;
}
