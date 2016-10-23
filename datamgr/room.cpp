#include <iostream>
#include <string>
#include <list>
#include "room.h"
#include "smartplug.h"
#include "user.h"



Room::Room()
{ 
    this->id = "";
    this->name = "";
    this->listUser = new list<User>();
    this->listSmartPlug = new list<SmartPlug>(); 
}

Room::Room(std::string id,std:: string name, std::list<User>listUser, std::list<SmartPlug>listSmartPlug)
{
	this->idRoom = idRoom;
	this->nameRoom = nameRoom;
	this->listUser = listUser;
	this->listSmartPlug = listSmartPlug;
}

std::string Room::getId()
{
	return this->id;
}

void Room::setId(std::string id)
{
	this->id = id;
}

std::string Room::getName()
{
	return this->name;
}

void Room::setName(std::string name)
{
	this->name = name;
}

std::list<User> Room::getListUser()
{
	return this->listUser;
}

void Room::setListUser(std::list<User>listUser)
{
	this->listUser = listUser;
}

std::list<SmartPlug> Room::getSmartPlug()
{
	return this->listSmartPlug;
}

void Room::setSmartPlug(std::list<SmartPlug>listSmartPlug)
{
	this->listSmartPlug = listSmartPlug;
}
