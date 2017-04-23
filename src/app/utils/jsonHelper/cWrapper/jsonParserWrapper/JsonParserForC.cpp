/***************************************************************************/
/*!
 * @file JsonParserForC.c
 * @brief
 *
 * Copyright (c) Tien Nguyen Anh
 *
 * @detail
 *
 * Modified History
 * ---------------
 * 2017-Jan-07 Created tien.nguyenanh94@gmail.com
 * 2017-Jan-12 Modified tn-trang.tran@outlook.com
 * 2017-Jan-18 Modified tn-trang.tran@outlook.com
 */
/***************************************************************************/

#include "JsonParserForC.h"
#include "JsonParser.h"

/*!
 * @internal
 */
bool parseDataSmartDeviceJsonForC(const char* jsonString, SmartDeviceInfo* info)
{
    return parseDataSmartDeviceJson(std::string(jsonString), *info);
}