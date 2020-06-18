#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void inverseYourName(string name, stack<char>& name_inside_paranthesis)
{
  for(string::iterator it=name.begin(); it!= name.end();it++)
  {
    if (*it == '(') {
      it++;
      while (*it!=')') {
        name_inside_paranthesis.push(*it);
        it++;
        if (*it==')') {
          break;
        }
      }
    }
  }
}

int main(int argc, char const *argv[]) {

  string name{"my name is (boyao)"};
  stack<char> name_inside_paranthesis;

  inverseYourName(name,name_inside_paranthesis);

  string nameInverse;

   while (!name_inside_paranthesis.empty()) {
    //std::cout << name_inside_paranthesis.top() << " ";
    nameInverse.push_back(name_inside_paranthesis.top());
    name_inside_paranthesis.pop();
  }

  name.replace(name.find('(')+1,nameInverse.size(),nameInverse); //replace(index,n,contents)
  std::cout << name << '\n';

  return 0;
}
