#include <iostream>
#include <string.h>
#include "smartplug.h"

int main()
{
	SmartPlug plug;

	strcpy(plug.id.idSmartPlug, "SP01");

	strcpy(plug.info.sender.ip, "192.168.0.100");

	plug.info.sender.port = 5563;

    strcpy(plug.info.data.smartPlugStatus, "ON");
    
	plug.info.datetimesp.monthSP = 1;
	plug.info.datetimesp.daySP = 22;
	plug.info.datetimesp.yearSP = 2017;
	plug.info.datetimesp.hourSP = 11;
	plug.info.datetimesp.minSP = 50;
	plug.info.datetimesp.secSP = 45;

	std::cout << "ID SmartPlug: " << plug.id.idSmartPlug <<std::endl;
	std::cout << "ipSmartPlug: " << plug.info.sender.ip <<std::endl;
	std::cout << "portSmartPlug: " << plug.info.sender.port <<std::endl;
	std::cout << "status: " << plug.info.data.smartPlugStatus <<std::endl;
	std::cout << "Date: " << plug.info.datetimesp.monthSP << "/" << plug.info.datetimesp.daySP << "/" << plug.info.datetimesp.yearSP <<std::endl;
	std::cout << "Time: " << plug.info.datetimesp.hourSP << ":" << plug.info.datetimesp.minSP << ":" << plug.info.datetimesp.secSP <<std::endl;
	
	return 0;
}