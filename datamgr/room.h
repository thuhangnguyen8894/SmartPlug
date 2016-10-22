#include <iostream>
#include <string>
#include <smartplug.h>

using namespace std;

class Room
{
	private:
		string idRoom;
		string nameRoom;
		list<User>listUser;
		list<SmartPlug>listSmartPlug;
	public:
		Room();
		Room(string idRoom, string nameRoom, list<User>listUser, list<SmartPlug>listSmartPlug);
		
		string getIdRoom();
		void setIdRoom(string idRoom);
		
		string getNameRoom();
		void setNameRoom(string nameRoom);
		
		list<User>getListUser();
		void setListUser(list<User>listUser);
		
		list<SmartPlug>getSmartPlug();
		void setListSmartPlug(list<SmartPlug>listSmartPlug);
};
