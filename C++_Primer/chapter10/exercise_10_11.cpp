#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class people {
private:
  string name;
  int age;

public:
  people(string name, int age):name(name),age(age){};
  virtual ~people (){};
  friend bool comparePeople(people &, people &);
  int yourage()
  {
    return age;
  }
  string yourname()
  {
    return name;
  }
};

bool comparePeople(people &p1, people &p2){
  return p1.yourage() < p2.yourage();
}

void rmDup(std::vector<string> &vs) {
  sort(vs.begin(),vs.end());
  auto it_end = unique(vs.begin(),vs.end());
  vs.erase(it_end,vs.end());
}

bool compareLength(string &s1, string &s2)
{
  return s1<s2;
}


int main(int argc, char const *argv[]) {

  std::vector<string> vs{"idiot","I","am","an","am","an"};
  rmDup(vs);
  //sort(vs.begin(),vs.end(),compareLength);
  sort(vs.begin(),vs.end(),[](const string &s1, const string &s2){return s1<s2;});
  for(auto value : vs)
  {
    std::cout << value << " ";
  }
  std::cout  << '\n';
  people jiechen("jiechen",26),boyao("boyao",25),zixin("zixin",24);

  std::cout << "before sorting" << '\n';

  std::vector<people> vp{jiechen,boyao,zixin};
  for(auto obj : vp)
  {
    std::cout << obj.yourname() << " " <<obj.yourage() << '\n';
  }

  sort(vp.begin(),vp.end(),comparePeople);

  std::cout << "after sorting" << '\n';

  for(auto obj : vp)
  {
    std::cout << obj.yourname() << " " <<obj.yourage() << '\n';
  }

  return 0;
}
