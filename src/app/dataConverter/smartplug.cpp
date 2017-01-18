#include <iostream>
#include <string>
#include "smartplug.h"


SmartPlug::SmartPlug()
{
    this->id = "";
    this->ip = "";
    this->status = "";

}



SmartPlug::SmartPlug(std::string id, std::string ip, std::string status)
{ 
    this->id = id;
    this->ip = ip;
    this->status = status;
}


std::string SmartPlug::getId()
{
	return this->id;
}

void SmartPlug::setId(std::string id)
{
	this->id = id;
}

std::string SmartPlug::getIP()
{
	return this->ip;
}

void SmartPlug::setIP(std::string ip)
{
	this->ip = ip;
}

std::string SmartPlug::getStatus()
{
	return this->status;
}

void SmartPlug::setStatus(std::string status)
{
	this->status = status;
}
