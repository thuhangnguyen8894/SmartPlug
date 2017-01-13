#ifndef ROOM_H
#define ROOM_H


#include <iostream>
#include <string>


class Room
{
    private:
        std::string id;
        std::string name;
        
        
    public:
        Room();
        Room(std::string id, std::string name);
		
        std::string getId();
        void setId(std::string id);
		
        std::string getName();
        void setName(std::string name);
};

#endif


