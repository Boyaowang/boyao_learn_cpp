#include <iostream>
#include <map>
using namespace std;

class Person
{
private:
  string name;
  int age;
public:
  Person();
  Person(string name, int age)
  :name(name), age(age)
  {};

  void print() {
    std::cout << name << " : " << age << '\n';
  };

};

int main(int argc, char const *argv[]) {
  map<int, Person> people;
  people[0] = Person("boyao", 25);
  return 0;
}
