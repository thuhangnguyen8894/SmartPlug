#include "smartplug.h"

using namespace std;

SmartPlug::SmartPlug(): idSmartPlug(""), addressIP(""), status(off)
{ }


SmartPlug::SmartPlug(string idSmartPlug, string addressIP, Status status): this->idSmartPlug(idSmartPlug), this->addressIP(addressIP), this->status(status)
{ }


string SmartPlug::getIdSmartPlug()
{
	return this->idSmartPlug;
}

void SmartPlug::setIdSmartPlug(string idSmartPlug)
{
	this->idSmartPlug = idSmartPlug;
}

string SmartPlug::getAddressIP()
{
	return this->addressIP;
}

void SmartPlug::setAddressIP(string addressIP)
{
	this->addressIP = addressIP;
}

Status SmartPlug::getStatus()
{
	return this->status;
}

void SmartPlug::setStatus(Status status)
{
	this->status = status;
}
