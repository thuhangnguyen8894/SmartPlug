#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <stdexcept>

#include <cppconn/connection.h>

#include "DBSmartPlug.h"
#include "DBSmartPlugForC.h"

bool update_to_db_ForC(const SmartDeviceInfo* smartplug)
{
	sql::Connection* con;

	DBSmartPlug db;

	bool status = db.update_to_db(con, *smartplug);
	return status;
}