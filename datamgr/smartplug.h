#include <iostream>
#include <string>

using namespace std;

enum Status{on, off};
class SmartPlug
{
private:
	string idSmartPlug;
	string addressIP;
	Status status;
public:
	SmartPlug();
	SmartPlug(string idSmartPlug, string addressIP, Status status);
	string getIdSmartPlug();
	void setIdSmartPlug(string idSmartPlug);
	string getAddressIP();
	void setAddressIP(string addressIP);
	Status getStatus();
	void setStatus(Status status);
	
};
