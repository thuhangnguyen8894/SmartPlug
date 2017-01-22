#ifndef ROOM_H
#define ROOM_H


#include <iostream>
#include <string>
#include <list>
#include "smartplug.h"

struct Room
{
    std::string id;
    std::string name;
    std::list<SmartPlug> *listSP;
};

#endif


