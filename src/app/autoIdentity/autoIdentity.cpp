#include "autoIdentity.h"

unsigned int numTableTimerInt = 0;

std::string getRawIdTimer(std::string numTableTimerStr)
{
	std::string rawIdTimerStr = "";
	unsigned int lenNumTableTimerStr = numTableTimerStr.length();

	if (lenNumTableTimerStr == 1)
	{
		rawIdTimerStr += "000000" + numTableTimerStr;
	}
	else if (lenNumTableTimerStr == 2)
	{
		rawIdTimerStr += "00000" + numTableTimerStr;
	}
	else if (lenNumTableTimerStr == 3)
	{
		rawIdTimerStr += "0000" + numTableTimerStr;
	}
	else if (lenNumTableTimerStr == 4)
	{
		rawIdTimerStr += "000" + numTableTimerStr;
	}
	else if (lenNumTableTimerStr == 5)
	{
		rawIdTimerStr += "00" + numTableTimerStr;
	}
	else if (lenNumTableTimerStr == 6)
	{
		rawIdTimerStr += "0" + numTableTimerStr;
	}
	else if (lenNumTableTimerStr == 7)
	{
		rawIdTimerStr += numTableTimerStr;
	}
	return rawIdTimerStr;
}

char* idTableTimer()
{
	std::string idTimerStr = "TI";

	std::stringstream numTableTimerStream;;
	numTableTimerStream << numTableTimerInt;
	std::string numTableTimerStr = numTableTimerStream.str();

	std::string rawIdTimerStr = getRawIdTimer(numTableTimerStr);

	idTimerStr += rawIdTimerStr;

	unsigned int lenIdTimer = idTimerStr.length();
	char* idTimerChar = new char[lenIdTimer + 1];
	strcpy(idTimerChar, idTimerStr.c_str());

	numTableTimerInt++;
	
	return idTimerChar;
}