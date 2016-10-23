#ifndef SMARTPLUG_H
#define SMARTPLUG_H 


#include <iostream>
#include <string>

class SmartPlug
{
private:
    string id;
    string ip;
    string status;
public:
    SmartPlug();
    SmartPlug(string id, string ip, string status);
    string getId();
    void setIdSmartPlug(string id);
    string getIP();
    void setIP(string IP);
    string getStatus();
    void setStatus(string status);
	
};

#endif
