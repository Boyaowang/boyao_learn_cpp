#ifndef WINDOWS_MGR_H
#define WINDOWS_MGR_H
#include "screen.H"
#include <vector>
#include <iostream>
using namespace std;

class windows_mgr {
public:
  typedef std::vector<screen>::size_type screenIndex;
private:
  std::vector<screen> screens{screen(24,80,' ')};

public:
  windows_mgr (){};
  virtual ~windows_mgr (){};

  void clear(screenIndex);
};

void windows_mgr::clear(screenIndex i){
  screen &s = screens[i];
  s.contents = string(s.height * s.width, ' ');
}

#endif
