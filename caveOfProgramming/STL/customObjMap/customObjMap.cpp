#include <iostream>
#include <map>
using namespace std;

class Person
{
private:
  string name;
  int age;
public:

  Person(){
        std::cout << "constructor 1" << '\n';
        //Still a question, why this constructor is called .....
  };

  Person(string name, int age)
  :name(name), age(age)
  {
    std::cout << "constructor 2" << '\n';
  };
  // copy constructor
  Person(const Person& obj)
  {
    name = obj.name;
    age = obj.age;
    std::cout << "copy constructor" << '\n';
  }

  void print() {
    std::cout << name << " : " << age << '\n';
  };

}jcbaba("name",99);

int main(int argc, char const *argv[]) {
  map<int, Person> people;

  people[0] = Person("boyao", 25);
  people[1] = Person("jiechen", 26);
  people[2] = Person("zixin", 24);

  people.insert(make_pair(5,Person("JC",100)));

  Person jiechenzheng("jiechen", 100);
  people[3]=jiechenzheng;

  std::cout << "***************************************************" << '\n';



  for (map<int, Person>::iterator it = people.begin(); it != people.end(); it++) {
    it->second.print();
    //std::cout << it->first << '\n';
  }

  return 0;
}
