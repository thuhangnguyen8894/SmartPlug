#include <iostream>
#include <sstream>
#include <memory>
#include <stdexcept>

#include <cppconn/connection.h>

#include "DBSmartDevice.h"
#include "DBSmartDeviceForC.h"

/*bool update_to_db_ForC(const SmartDeviceInfo* device)
{
	sql::Connection* con;

	DBSmartDevice db;

	bool status = db.update_to_db(con, *device);
	return status;
}*/

bool insert_to_table_Timer_ForC(const SmartDeviceInfo* device)
{
	sql::Connection* con;

	DBSmartDevice db;

	bool status = db.insert_to_table_Timer(con, *device);
	return status;
}

bool insert_to_table_Device_Timer_ForC(const SmartDeviceInfo* device)
{
	sql::Connection* con;

	DBSmartDevice db;

	bool status = db.insert_to_table_Device_Timer(con, *device);
	return status;
}