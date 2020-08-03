#include <iostream>
#include "Message.H"

//class Message
Message::Message(const Message& msg):contents(msg.contents),folders(msg.folders)
{
  add_to_Folders(msg);
};

Message& Message::operator=(const Message& rhs)
{
  remove_from_Folders();
  this->contents = rhs.contents;
  this->folders = rhs.folders;
  add_to_Folders(rhs);
  return *this;
};

void Message::save(Folder &f)
{
  this->folders.insert(&f);
  f.addMsg(this);
};

void Message::remove(Folder &f)
{
  this->folders.erase(&f);
  f.remMsg(this);
};

void Message::add_to_Folders(const Message& msg)
{
  for(auto f:msg.folders)
  {
    f->addMsg(this);
  }
};

void Message::remove_from_Folders()
{
  for(auto f:folders)
  {
    f->remMsg(this);
  }
};

//class Folder
Folder::Folder(const Folder &f):Messages(f.Messages)
{
  add_to_Messages(f);
};

Folder &Folder::operator=(const Folder& rhs)
{
  remove_from_Messages();
  this->Messages=rhs.Messages;
  add_to_Messages(rhs);
};

void Folder::add_to_Messages(const Folder &f)
{
  for(auto msg:f.Messages)
  {
    msg->addFldr(this);
  }
};

Folder::~Folder()
{
  remove_from_Messages();
};

void Folder::remove_from_Messages()
{
  for(auto msg:Messages)
  {
    msg->remFldr(this);
  }
};

void Folder::print()
{
  for(auto msg:Messages)
  {
    std::cout << (*msg).contents << '\n';
  }
}
