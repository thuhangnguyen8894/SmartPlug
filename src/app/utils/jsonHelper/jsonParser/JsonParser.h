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

#include "DataDef.h"
#include "JsonCommon.h"

bool parseLightInteJson(const char* jsonString, LightIntensityInfo* info);

#endif