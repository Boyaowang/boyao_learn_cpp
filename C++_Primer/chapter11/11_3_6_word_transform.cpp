#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

std::map<string, string> trans_map(ifstream& input_file){
  std::map<string, string> map_trans;
  string word,phrase;
  while (input_file >> word && getline(input_file, phrase)) {
    if (phrase.size() > 1) {
      map_trans[word] = phrase.substr(1);
    } else {
      throw runtime_error("no rule for " + word);
    }
  }
  return map_trans;
};

const string& transform(const string& words, std::map<string, string> transMap)
{
  auto it = transMap.find(words);
  if ( it != transMap.end()) {
    return it->second;
  }else{
    return words;
  }
}

int main(int argc, char const *argv[]) {
  ifstream input_map("map_file");
  ifstream input_text("file_to_transform");
  std::map<string, string> map_to_use = trans_map(input_map);
  // for(auto value:map_to_use)
  // {
  //   std::cout << value.first << " " << value.second << '\n';
  // }
  //
  // string testwords = "k";
  // std::cout << transform(testwords,map_to_use) << '\n';
  string text;
  while (getline(input_text,text)) {
    istringstream texstream(text);
    string word;
    while (texstream>>word) {
      std::cout << transform(word,map_to_use) << " ";
    }
    std::cout << endl;
  }
  return 0;
}
