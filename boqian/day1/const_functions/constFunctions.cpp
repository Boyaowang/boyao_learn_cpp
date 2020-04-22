#include <iostream>
using namespace std;

class dog
{
private:

  int age;
  string name = "unknown";
  mutable string gender = "unknown"; // const can be changed if mutable is used

public:

  dog(int age, string name): age(age), name(name){};

  // const fucntion: which make sure it will not change any value inside the class

  void getAge() const
  {
    // age =100; is not possible

    std::cout << "The age of the dog is(const) " << age << endl;

  };

  void getAge()
  {
    std::cout << "The age of the dog is(non-const) " << age << endl;
  };

  void setGender(string gender) const
  {
    this->gender = gender;
  };

  void getGender() const
  {
    std::cout << "The gender of your dog is " << gender << '\n';
  };

};

void printDogAge(const dog& yourDog)
{
  yourDog.getAge();
};

int main(int argc, char const *argv[]) {

  dog a(10,"lf");
  const dog b(5,"lf2");

  a.getAge();
  b.getAge();

  printDogAge(a);
  printDogAge(b);

  a.setGender("male");
  a.getGender();

  return 0;
}
