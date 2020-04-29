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
  //  std::cout << "constructor 2" << '\n';
  };
  // copy constructor
  Person(const Person& obj)
  {
    name = obj.name;
    age = obj.age;
  //  std::cout << "copy constructor" << '\n';
  }

  void print() const{
    std::cout << name << " : " << age << ' ';
  };

// operator overloading for sorting in map
  bool operator < (const Person& obj) const
  {
      if (name==obj.name) {
        return age<obj.age;
      } else {
        return name<obj.name;
      }
  }

} ;

int main(int argc, char const *argv[]) {

  map<Person, int> people;
  people[Person("jiechen",26)] = 0;
  people[Person("boyao",25)] = 1;
  people[Person("zixin",25)] = 2;
  people[Person("boyao",29)] = 2;
//  std::cout << "***************************************************" << '\n';


  for (map<Person, int>::iterator it = people.begin(); it != people.end(); it++) {
    it->first.print();

    std::cout << it->second << '\n';
  }

/*
  string a= "namg";
  string b = "namf";
  bool compare = (a<b);
  std::cout << compare << '\n';
  */
  return 0;
}
