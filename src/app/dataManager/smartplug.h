#ifndef SMARTPLUG_H
#define SMARTPLUG_H 


#include <iostream>
#include <string>
#include "DataDef.h"

typedef struct
{
    char idSmartDevice[SIZE_ID];
    SmartDeviceInfo info;
}Devices;

#endif
