#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
void sortAndRmDup(std::vector<T> v) {
  sort(v.begin(),v.end());
  auto it_end = unique(v.begin(),v.end());
  v.erase(it_end,v.end());
}

bool isShorter(const string &s1, const string &s2)
{
  return s1.size() < s2.size();
}

//template<class T>
typedef void (*pSortAndRmDup) (std::vector<string> v);

void biggies(std::vector<string> &words, std::vector<string>::size_type sz, pSortAndRmDup sorting) {
  sorting(words);
  stable_sort(words.begin(),words.end(),isShorter);
  //auto it_appear = find_if(words.begin(),words.end(),[sz](const string &s){return s.size()>=sz;});
  auto it_appear = stable_partition(words.begin(),words.end(),[sz](const string s)->bool{return s.size()<=sz;});
  auto count = words.end() - it_appear;
  std::cout << "There are " << count << " words longer than the size of " << sz << '\n';
  std::cout << "They are " << '\n';
  // for (std::vector<string>::iterator it = it_appear; it!=words.end(); it++) {
  //   std::cout << *it << " ";
  // }
  for_each(it_appear,words.end(),[](const string &s){std::cout << s << " ";});

}

int main(int argc, char const *argv[]) {
  std::vector<string> vs{"I","am","an","am","an","idiot","or","not","fuck!!"};
  biggies(vs,3,sortAndRmDup);
  return 0;
}
