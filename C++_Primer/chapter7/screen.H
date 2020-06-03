#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
using namespace std;

class screen {
public:
  friend class windows_mgr;
public:
  typedef std::string::size_type pos;
private:
  pos cursor = 0;
  pos height = 0, width = 0;
  string contents;
  mutable int mutNum =10;

  screen *pscreen;

  void do_display(ostream& os) const{
    os << contents;
  }

public:
  screen () = default;
  screen(pos ht, pos wd, char c):height(ht), width(wd), contents(ht*wd,c){};
  virtual ~screen (){};

// get() functions

  char get()const{
    return contents[cursor];
  }

  inline char get(pos r, pos c) const;

// move() function

  screen &move(pos r, pos c);

// set() functions

  screen &set(char c);
  screen &set(pos r, pos c, char ch);

// test mutable

  void printMutalble() {
    std::cout << ++mutNum << '\n';
  }

// display() functions

  screen &display(ostream& os){
    do_display(os);
    return *this;
  }

  const screen &display(ostream& os)const{
    do_display(os);
    return *this;
  }

};

  char screen::get(pos r, pos c) const{
    pos row = r * width;
    return contents[row+c];
  }

  inline screen &screen::move(pos r, pos c){
    pos row = r*width;
    cursor = row + c;
    return *this;
  }

  inline screen &screen::set(char c)
  {
    contents[cursor] = c;
    return *this;
  };
  inline screen &screen::set(pos r, pos c, char ch)
  {
    contents[r*width + c] = ch;
    return *this;
  };

  #endif
