/*****************************************************************************/
/*!
 * @file JsonParser.h
 * @brief The declaration of JsonParser.
 *
 * Copyright (c) Trang Tran 2017
 *
 * @detail 
 *
 * Modified History
 * ---------------
 * 2017-Jan-05 Created tn-trang.tran@outlook.com
 */
/*****************************************************************************/

#ifndef __JSON_PARSER_H__
#define __JSON_PARSER_H__

#include "DataDef.h"
#include "JsonCommon.h"

bool parseSmartPlugJson(const char* jsonString, smartplugInfo* info);

#endif