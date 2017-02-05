#ifndef ROOM_H
#define ROOM_H


#include <iostream>
#include <string.h>
#include <list>
#include "smartplug.h"

typedef struct
{
    char idRoom[10];
    char nameRoom[10];
    std::list<SmartPlug> *listSP;
}Room;

#endif


