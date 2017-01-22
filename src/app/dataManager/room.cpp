#include <iostream>
#include <string>

#include "room.h"

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
	
	SmartPlug plug1 = {"SP02", "192.168.0.101", 5563, "OFF", {56, 45, 14, 12, 02, 2017}};
	std::cout << "ID SmartPlug 1: " << plug1.idSmartPlug <<std::endl;
	std::cout << "ipSmartPlug 1: " << plug1.ipSmartPlug <<std::endl;
	std::cout << "portSmartPlug 1: " << plug1.portSmartPlug <<std::endl;
	std::cout << "status 1: " << plug1.status <<std::endl;
	std::cout << "Date 1: " << plug1.dateTimeSP.monthSP << "/" << plug1.dateTimeSP.daySP << "/" << plug1.dateTimeSP.yearSP <<std::endl;
	std::cout << "Time 1: " << plug1.dateTimeSP.hourSP << ":" << plug1.dateTimeSP.minSP << ":" << plug1.dateTimeSP.secSP <<std::endl;

    Room room;
    room.idRoom = "R001";
    room.nameRoom = "Bedroom";
    room.listSP->push_back(plug);
    room.listSP->push_back(plug1);

    std::cout << "ID Room " << room.idRoom << std::endl;
    std::cout << "Name: " << room.nameRoom << std:: endl;
    std::cout << "listSP: " << room.listSP << std::endl;

	return 0;
}