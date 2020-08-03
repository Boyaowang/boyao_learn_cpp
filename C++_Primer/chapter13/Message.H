#ifndef Message_H_
#define Message_H_

#include <string>
#include <set>

class Folder;
class Message{
  friend class Folder;
public:
  //constructor, copy constructor, copy assignment
  explicit Message(const std::string &s = ""):contents(s){};
  Message(const Message&);
  Message &operator=(const Message&);
  //destructor
  ~Message(){remove_from_Folders();};
  //save to and remove from folders
  void save(Folder&);
  void remove(Folder&);
  void addFldr(Folder *f){folders.insert(f);};
  void remFldr(Folder *f){folders.erase(f);};
private:
  std::string contents;
  std::set<Folder*> folders;
  //add to and remove from Folders
  void add_to_Folders(const Message&);
  void remove_from_Folders();
};

class Folder{
  friend class Message;
public:
  //constructor, copy constructor, copy assignment
  Folder()=default;
  Folder(const Folder&);
  Folder &operator=(const Folder&);
  //destructor
  ~Folder();
  void addMsg(Message *msg){Messages.insert(msg);};
  void remMsg(Message *msg){Messages.erase(msg);};
  void print();
private:
  std::set<Message*> Messages;
  // add to Message sets
  void add_to_Messages(const Folder&);
  void remove_from_Messages();
};
#endif
