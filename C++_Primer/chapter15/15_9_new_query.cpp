#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <map>
#include <sstream>
#include <set>
#include <algorithm>

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
  QueryResult query(const string &sought)const;
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

  set<line_no>::iterator begin(){ return lines->begin(); }
  set<line_no>::iterator end(){ return lines->end(); }
  shared_ptr<vector<string>> get_file(){ return file; }
  virtual ~QueryResult (){};
};

QueryResult TextQuery::query(const string &sought)const{
  static shared_ptr<set<line_no>> nodata(new set<line_no>);
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
  os << qr.sought << " occurs " << qr.lines->size() << " "<<make_plural(qr.lines->size(),"time","s") << endl;
  for(auto num : *(qr.lines))
  {
    os << "\t(line " << num+1 << ") " << *(qr.file->begin() + num) << endl;
  }
};

void runQuery(ifstream &infile,string s) {
  TextQuery tq(infile);
  print(cout, tq.query(s));
}

class Query_base {
  friend class Query;
protected:
  using line_no = ::line_no;
  virtual ~Query_base ()= default;
private:
  virtual QueryResult eval(const TextQuery&) const = 0;
  virtual string rep() const = 0;
};

class Query {
  friend Query operator~(const Query&);
  friend Query operator&(const Query&, const Query&);
  friend Query operator|(const Query&, const Query&);
private:
  Query(shared_ptr<Query_base> query): q(query){};
  shared_ptr<Query_base> q;

public:
  Query (const string&);
  QueryResult eval(const TextQuery &t) const
  {return q->eval(t);}
  string rep()const
  {return q->rep();};
};

ostream& operator << (ostream &os, const Query &query)
{
  return os << query.rep();
}

class WordQuery :public Query_base{
  friend class Query;
  WordQuery(const string &s):query_word(s){};
  QueryResult eval(const TextQuery &t) const
  {
    return t.query(query_word);
  }
  string rep()const{return query_word;}
  string query_word;
};

inline Query::Query(const string &s):q(new WordQuery(s)){};

class NotQuery:public Query_base{
  friend Query operator~(const Query &);
  NotQuery(const Query& q):query(q){};
  string rep() const {return "~(" + query.rep() + ")";};
  QueryResult eval(const TextQuery&) const;
  Query query;
};

inline Query operator~(const Query &operand)
{
  return std::shared_ptr<Query_base>(new NotQuery(operand));
}

class BinaryQuery:public Query_base {
protected:
  BinaryQuery (const Query &l, const Query &r, const string s):lhs(l),rhs(r),opSym(s){};
  string rep() const
  {
    return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
  }
  Query lhs,rhs;
  string opSym;
};

class AndQuery:public BinaryQuery {
friend Query operator&(const Query &,const Query &);
AndQuery(const Query &left, const Query &right):BinaryQuery(left, right, "&"){};
QueryResult eval(const TextQuery&) const;
};

inline Query operator&(const Query &lhs,const Query &rhs){
  return shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}

class OrQuery:public BinaryQuery {
friend Query operator|(const Query &,const Query &);
OrQuery(const Query &left, const Query &right):BinaryQuery(left, right, "|"){};
QueryResult eval(const TextQuery&) const;
};

inline Query operator|(const Query &lhs,const Query &rhs){
  return shared_ptr<Query_base>(new OrQuery(lhs,rhs));
}

QueryResult OrQuery::eval(const TextQuery& text)const
{
  QueryResult right = rhs.eval(text), left = lhs.eval(text); // or auto
  auto ret_lines = make_shared<set<line_no>> (left.begin(),left.end());
  ret_lines->insert(right.begin(),right.end());
  return QueryResult(rep(), left.get_file(),ret_lines);
}

QueryResult AndQuery::eval(const TextQuery& text)const
{
  QueryResult right = rhs.eval(text), left = lhs.eval(text); // or auto
  auto ret_lines = make_shared<set<line_no>> ();
  set_intersection(left.begin(),left.end(),right.begin(),right.end(),inserter(*ret_lines,ret_lines->begin()));
  return QueryResult(rep(), left.get_file(),ret_lines);
}

QueryResult NotQuery::eval(const TextQuery& text)const
{
  auto result = query.eval(text);
  auto ret_lines = make_shared<set<line_no>>();
  auto beg = result.begin(), end = result.end();
  auto sz = result.get_file()->size();
  for (size_t n = 0; n != sz; ++n) {
    if (beg == end || *beg !=n) {
      ret_lines->insert(n);
    } else if (beg!=end) {
      ++beg;
    }
  }
  return QueryResult(rep(),result.get_file(),ret_lines);
}

int main(int argc, char const *argv[]) {
  ifstream axin("girlFriend");
  TextQuery zixin(axin);
  Query q = ~Query("aa") ;
  auto result = q.eval(zixin);
  print(cout,result);
  return 0;
}
