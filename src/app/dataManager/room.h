#ifndef ROOM_H
#define ROOM_H


#include <iostream>
#include <string>
#include <list>
#include "smartplug.h"

typedef struct
{
    std::string idRoom;
    std::string nameRoom;
    std::list<SmartPlug> *listSP;
}Room;

#endif


