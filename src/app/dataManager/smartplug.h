#ifndef SMARTPLUG_H
#define SMARTPLUG_H 


#include <iostream>
#include <string>
#include "DataDef.h"

typedef struct
{
    std::string idSmartPlug;
    std::string ipSmartPlug;
    int portSmartPlug;
    SmartPlugStatus status;
    DatetimeSP dateTimeSP;
}SmartPlug;

#endif
