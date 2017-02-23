#include <iostream>
#include <sstream>
#include <memory>
#include <stdexcept>

#include <cppconn/connection.h>

#include "DBSmartPlug.h"
#include "DBSmartPlugForC.h"

/*bool update_to_db_ForC(const SmartDeviceInfo* smartplug)
{
	sql::Connection* con;

	DBSmartPlug db;

	bool status = db.update_to_db(con, *smartplug);
	return status;
}*/

bool update_to_db_ForC(const char* stateElectric, const char* stateRelay, const char* ip_port_jack)
{
	sql::Connection* con;

	DBSmartPlug db;

	bool status = db.update_to_db(con, std::string(stateElectric), std::string(stateRelay), std::string(ip_port_jack));
	return status;
}