#include "room.h"

using namespace std;


Room::Room(): idRoom(""), nameRoom(""), listUser(new list<User>() ), listSmartPlug(new list<SmartPlug>())
{ }

Room::Room(string idRoom, string nameRoom, list<User>listUser, list<SmartPlug>listSmartPlug)
{
	this->idRoom = idRoom;
	this->nameRoom = nameRoom;
	this->listUser = listUser;
	this->listSmartPlug = listSmartPlug;
}

string Room::getIdRoom()
{
	return this->idRoom;
}

void Room::setIdRoom(string idRoom)
{
	this->idRoom = idRoom;
}

string Room::getNameRoom()
{
	return this->nameRoom;
}

void Room::setNameRoom(string nameRoom)
{
	this->nameRoom = nameRoom;
}

list<User>Room::getListUser()
{
	return this->listUser;
}

void Room::setListUser(list<User>listUser)
{
	this->listUser = listUser;
}

list<SmartPlug>Room::getSmartPlug()
{
	return this->listSmartPlug;
}

void Room::setSmartPlug(list<SmartPlug>listSmartPlug)
{
	this->listSmartPlug = listSmartPlug;
}
