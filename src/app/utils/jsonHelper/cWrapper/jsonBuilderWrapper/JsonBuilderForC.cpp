/***************************************************************************/
/*!
 * @file JsonBuilderForC.c
 * @brief
 *
 * Copyright (c) Tien Nguyen Anh
 *
 * @detail
 *
 * Modified History
 * ---------------
 * 2017-Jan-07 Created tien.nguyenanh94@gmail.com
 */
/***************************************************************************/

#include <iostream>
#include <string>
#include <string.h>

#include "JsonBuilderForC.h"

/*!
 * @internal
 */
bool buildJsonForC(const char* message, char** jsonString)
{
	std::string jsonStringStr;
	bool status = buildJson(std::string(message), jsonStringStr);
	*jsonString = strdup(jsonStringStr.c_str());
	return status;
}