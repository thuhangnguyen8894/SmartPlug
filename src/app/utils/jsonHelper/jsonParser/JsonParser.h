/*****************************************************************************/
/*!
 * @file JsonParser.h
 * @brief The declaration of JsonParser.
 *
 * Copyright (c) Tien Nguyen Anh
 *
 * @detail 
 *
 * Modified History
 * ---------------
 * 2017-Jan-05 Created tien.nguyenanh94@gmail.com
 * 2017-Jan-07 Modified tn-trang.tran@outlook.com
 * 2017-Jan-11 Modified tn-trang.tran@outlook.com
 * 2017-Jan-18 Modified tn-trang.tran@outlook.com
 */
/*****************************************************************************/

#ifndef __JSON_PARSER_H__
#define __JSON_PARSER_H__

#include <iostream>
#include <string>
#include <math.h>
#include <regex>
#include <string.h>

#include "JsonCommon.h"

/*!
 * @brief
 * param[in] message
 * return
 */
bool parseDataSmartDeviceJson(const std::string& jsonString,
                                                SmartDeviceInfo& info);

bool parseJsonToTopic(const std::string& jsonString, std::string& topic);

#endif