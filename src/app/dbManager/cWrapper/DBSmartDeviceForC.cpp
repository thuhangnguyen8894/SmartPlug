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

bool selectDeviceToTableSmartDeviceForC(SmartDeviceInfo** device, 
														 int *numberOfElement)
{
	if (*device != NULL)
    {
        delete *device;
        *device = NULL;
    }

    int index = 0;

    SmartDeviceInfo* listSmartDeviceInfoTmp = new SmartDeviceInfo[2];
    std::vector<SmartDeviceInfo> vectorSmartDeviceInfos;
    bool result = db.selectDeviceToTableSmartDevice(vectorSmartDeviceInfos);

    if (!result)
    {
        return false;
    }

	*numberOfElement = vectorSmartDeviceInfos.size();
    for (index = 0; index < *numberOfElement; index++)
    {
        strcpy((listSmartDeviceInfoTmp[index]).device.idSmartDevice,
                          vectorSmartDeviceInfos[index].device.idSmartDevice);
        strcpy((listSmartDeviceInfoTmp[index]).device.nameSmartDevice,
                          vectorSmartDeviceInfos[index].device.idSmartDevice);
    }
   
    *device = listSmartDeviceInfoTmp;

    return true;
}