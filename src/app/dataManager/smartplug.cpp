#include <iostream>
#include <string>
#include "smartplug.h"

int main()
{
	SmartPlug plug;
	plug.idSmartPlug = "SP01";
	plug.ipSmartPlug = "192.168.0.100";
	plug.portSmartPlug = 5563;
	plug.status = "ON";
	plug.dateTimeSP.monthSP = 01;
	plug.dateTimeSP.daySP = 22;
	plug.dateTimeSP.yearSP = 2017;
	plug.dateTimeSP.hourSP = 11;
	plug.dateTimeSP.minSP = 50;
	plug.dateTimeSP.secSP = 45;

	std::cout << "ID SmartPlug: " << plug.idSmartPlug <<std::endl;
	std::cout << "ipSmartPlug: " << plug.ipSmartPlug <<std::endl;
	std::cout << "portSmartPlug: " << plug.portSmartPlug <<std::endl;
	std::cout << "status: " << plug.status <<std::endl;
	std::cout << "Date: " << plug.dateTimeSP.monthSP << "/" << plug.dateTimeSP.daySP << "/" << plug.dateTimeSP.yearSP <<std::endl;
	std::cout << "Time: " << plug.dateTimeSP.hourSP << ":" << plug.dateTimeSP.minSP << ":" << plug.dateTimeSP.secSP <<std::endl;
	
	return 0;
}