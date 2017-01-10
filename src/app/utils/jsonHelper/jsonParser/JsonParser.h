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
 * 2017-Jan-03 Created tien.nguyenanh94@gmail.com
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
bool parseSmartPlugStatusJson(const std::string& jsonString,
                                                SmartPlugInfo& info);

#endif