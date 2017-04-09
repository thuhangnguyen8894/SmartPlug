#include <iostream>
#include <sstream>
#include <memory>
#include <stdexcept>

#include <cppconn/connection.h>

#include "DBSmartDevice.h"
#include "DBSmartDeviceForC.h"

static DBSmartDevice db;

bool insertToTableTimerForC(const SmartDeviceInfo* device)
{
	sql::Connection* con;

	bool status = db.selectIdTimerToTableTimer(con, *device);
	return status;
}

bool insertToTableDeviceTimerForC(const SmartDeviceInfo* device)
{
	sql::Connection* con;

	bool status = db.insertToTableDeviceTimer(con, *device);
	return status;
}

bool selectIdTimerToTableTimerForC(SmartDeviceInfo* device)
{
	sql::Connection* con;

	bool status = db.selectIdTimerToTableTimer(con, *device);
	return status;
}