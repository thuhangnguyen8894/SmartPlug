#include <iostream>
#include <string>
#include "smartplug.h"

SmartPlug::SmartPlug()
{
	this->id = "";
    	this->ip = "";
    	this->status = "";
}


SmartPlug::SmartPlug(string id, string ip, string status)
{
	this->id = id;
	this->ip = ip;
	this->status = status;
}


string SmartPlug::getId()
{
	return this->id;
}

void SmartPlug::setId(string id)
{
	this->id = id;
}

string SmartPlug::getIP()
{
	return this->ip;
}

void SmartPlug::setIP(string ip)
{
	this->ip = ip;
}
string SmartPlug::getStatus()
{
	return this->status;
}

void SmartPlug::setStatus(string status)
{
	this->status = status;
}
