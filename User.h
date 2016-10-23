#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <list>
#include "Room.h"
#include "UserStyle.h"

Class User
{
    private:
       std::string id;
       std::string username;
       std::string password;
       list<Room> listRoom;
       list<UserStyle> listUS;
    
    public:
    User();
    User(string id, string username, string password,
	 list<Room> listRoom, list<UserStyle> listUserStyle);

    void setId(string id);
    string getId();

    void setUserName(string username);
    string getUserName();

    void listRoom(list<Room> listRoom);
    list<Room> getListRoom();

    void setListUserStyle(list<UserStyle> listUserStyle);
    list<UserStyle> getListUserStyle();
};

#endif
