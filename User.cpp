#include <iostream>
#include "User.h"
#include "UserStyle.h"

User::User()
{
     this->id = "";
     this->username = "";
     this->password = "";
     this->listRoom = new list<Room>();
     this->listUserStyle = new list<UserStyle>();
}

User::User(string id, string username, string password,
     list<Room> listRoom, list<UserStyle> listUserStyle)
{
     this->id = id;
     this->username = username;
     this->password = password;
     this->listRoom = new list<Room> (listRoom);
     this->listUserStyle = new list<UserStyle>(listUserStyle);
}

void User::setId(string id)
{
     this->id = id;
} 

string User::getId()
{
     return id;
}

void User::setUserName(string username)
{
     this->username  = username;
}

string std::getUserName()
{
     return username;
}

void setListRoom(list<Room> listRoom)
{
     this->listRoom = listRoom;
}

list<Room> getListRoom()
{
     return listRoom;
}

void setListUserStyle(list<UserStyle> listUserStyle)
{
     this->listUserStyle = listUserStyle;
}

list<UserStyle> getListUserStyle()
{
     return listUserStyle;
}
