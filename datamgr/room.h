#ifndef ROOM_H
#define ROOM_H


#include <iostream>
#include <string>
#include <smartplug.h>

class Room
{
    private:
        std::string id;
        std::string name;
        list<User>listUser;
        list<SmartPlug>listSmartPlug;
    public:
        Room();
        Room(std::string id, std::string name, list<User>listUser, list<SmartPlug>listSmartPlug);
		
        std::string getId();
        void setId(std::string id);
		
        std::string getName();
        void setName(std::string name);
		
        list<User>getListUser();
        void setListUser(list<User>listUser);
		
        list<SmartPlug>getSmartPlug();
        void setListSmartPlug(list<SmartPlug>listSmartPlug);
};

#endif


