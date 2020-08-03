#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <map>
#include <sstream>
#include <set>

using namespace std;

typedef std::vector<string>::size_type line_no;
class QueryResult;
class TextQuery {
private:
  shared_ptr<std::vector<string>> file;
  std::map<string, shared_ptr<set<line_no>>> wm;

public:
  TextQuery (){};
  TextQuery(ifstream &);
  QueryResult query(const string &sought);
  virtual ~TextQuery (){};
};

TextQuery::TextQuery(ifstream &is):file(new std::vector<string>)
{
  string text;
  while (getline(is,text)) {
    file->push_back(text);
    int n = file->size()-1;
    istringstream line(text);
    string word;
    while (line>>word) {
      auto &lines = wm[word];
      if (!lines) {
        lines.reset(new set<line_no>);
      }
      lines->insert(n);
    }
  }
}

class QueryResult {
public:
  friend ostream &print(ostream&, const QueryResult&);
private:
  string sought;
  shared_ptr<std::vector<string>> file;
  shared_ptr<set<line_no>> lines;
public:
  QueryResult (string sought,
               shared_ptr<std::vector<string>> file,
               shared_ptr<set<line_no>> lines)
               :sought(sought),file(file),lines(lines){};
  virtual ~QueryResult (){};
};

QueryResult TextQuery::query(const string &sought){
  static shared_ptr<set<line_no>> nodata;
  auto loc = wm.find(sought);
  if (loc == wm.end()) {
    return QueryResult(sought,file,nodata);
  } else {
    return QueryResult(sought,file,loc->second);
  }
};

string make_plural(size_t size, const string &word, const string &ending)
{
  return (size>1)? word + ending : word;
}

ostream &print(ostream &os, const QueryResult &qr){
  os << qr.sought << " occurs " << " " << qr.lines->size() <<make_plural(qr.lines->size(),"time","s") << endl;
  for(auto num : *(qr.lines))
  {
    os << "\t(line " << num+1 << ") " << *(qr.file->begin() + num) << endl;
  }
};

void runQuery(ifstream &infile,string s) {
  TextQuery tq(infile);
  print(cout, tq.query(s));
}

int main(int argc, char const *argv[]) {
  ifstream inputfile("girlFriend");
  runQuery(inputfile,"zixin");
  return 0;
}
