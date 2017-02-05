#ifndef SMARTPLUG_H
#define SMARTPLUG_H 


#include <iostream>
#include <string>
#include "DataDef.h"

typedef struct 
{
	char idSmartPlug[10];
}SmartPlugIdentity;

typedef struct
{
    SmartPlugIdentity id;
    SmartPlugInfo info;
}SmartPlug;

#endif
