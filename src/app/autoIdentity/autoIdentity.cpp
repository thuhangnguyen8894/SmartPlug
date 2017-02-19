#include "autoIdentity.h"

unsigned int numTableTimerInt = 0;

char* idTableTimer()
{
	std::string idTimerStr = "TI000";

	std::stringstream numTableTimerStream;;
	numTableTimerStream << numTableTimerInt;
	std::string numTableTimerStr = numTableTimerStream.str();

	idTimerStr += numTableTimerStr;

	unsigned int lenIdTimer = idTimerStr.length();
	char* idTimerChar = new char[lenIdTimer + 1];
	strcpy(idTimerChar, idTimerStr.c_str());

	numTableTimerInt++;
	
	return idTimerChar;
}