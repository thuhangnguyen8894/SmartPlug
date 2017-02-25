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
 * 2017-Jan-11 Modified tn-trang.tran@outlook.com
 * 2017-Jan-18 Modified tn-trang.tran@outlook.com
 */
/***************************************************************************/

#include <iostream>
#include <string>
#include <string.h>

#include "JsonBuilder_smart_device_status_value_ForC.h"
#include "JsonBuilder_smart_device_status_value.h"

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