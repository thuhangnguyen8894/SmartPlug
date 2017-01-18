#ifndef SMARTPLUG_H
#define SMARTPLUG_H 


#include <iostream>
#include <string>

class SmartPlug
{
private:
    std::string id;
    std::string ip;
    std::string status;
public:
    SmartPlug();
    SmartPlug(std::string id, std::string ip, std::string status);
    std::string getId();
    void setId(std::string id);
    std::string getIP();
    void setIP(std::string ip);
    std::string getStatus();
    void setStatus(std::string status);
	
};

#endif
