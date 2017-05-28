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
	bool status = db.insertToTableTimer(*device);
	return status;
}

bool insertToTableDeviceTimerForC(const SmartDeviceInfo* device)
{
	bool status = db.insertToTableDeviceTimer(*device);
	return status;
}

bool selectIdTimerToTableTimerForC(SmartDeviceInfo* device)
{
	bool status = db.selectIdTimerToTableTimer(*device);
	return status;
}