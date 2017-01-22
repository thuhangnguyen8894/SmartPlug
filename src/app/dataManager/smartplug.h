#ifndef SMARTPLUG_H
#define SMARTPLUG_H 


#include <iostream>
#include <string>
#include "DataDef.h"

typedef struct
{
    std::string id;
    std::string ipSmartPlug;
    int portSmartPlug;
    std::string status;
    DatetimeSP dateTimeSP;
}Plug;

#endif
