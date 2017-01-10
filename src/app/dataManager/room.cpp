#include <iostream>
#include <string>

#include "room.h"





Room::Room()
{ 
    this->id = "";
    this->name = "";
}

Room::Room(std::string id,std:: string name)
{
	this->id = id;
	this->name = name;
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

