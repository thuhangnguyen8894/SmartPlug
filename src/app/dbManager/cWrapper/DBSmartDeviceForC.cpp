#include <iostream>
#include <sstream>
#include <memory>
#include <stdexcept>

#include <cppconn/connection.h>

#include "DBSmartDevice.h"
#include "DBSmartDeviceForC.h"

static DBSmartDevice db;

bool insert_to_table_Timer_ForC(const SmartDeviceInfo* device)
{
	sql::Connection* con;

	bool status = db.insert_to_table_Timer(con, *device);
	return status;
}

bool insert_to_table_Device_Timer_ForC(const SmartDeviceInfo* device)
{
	sql::Connection* con;

	bool status = db.insert_to_table_Device_Timer(con, *device);
	return status;
}

bool select_idTimer_to_table_Timer_ForC(SmartDeviceInfo* device)
{
	sql::Connection* con;

	bool status = db.select_idTimer_to_table_Timer(con, *device);
	return status;
}