#include <iostream>
using namespace std;

const string shorterString(const string &s1, const string &s2)
{
  return (s1.size() <= s2.size()) ? s1 : s2;
}

string shorterString(string &s1, string &s2)
{
  const string result = shorterString(const_cast<const string &> (s1), const_cast<const string &> (s2));
  return const_cast<string&> (result);
}

void print(int){};

int main(int argc, char const *argv[]) {

  string s1 ="boyao";
  string s2 ="boyaowang";
  std::cout << shorterString(s1,s2) << '\n';

  return 0;
}
