/***************************************************************************/
/*!
 * @file JsonParserForC.h
 * @brief
 *
 * Copyright (c) Tien Nguyen Anh
 *
 * @detail
 *
 * Modified History
 * ---------------
 * 2017-Jan-07 Created tien.nguyenanh94@gmail.com
 * 2017-Jan-13 Modified tn-trang.tran@outlook.com
 * 2017-Jan-18 Modified tn-trang.tran@outlook.com
 */
/***************************************************************************/

#ifndef __JSON_PARSER_FOR_C__
#define __JSON_PARSER_FOR_C__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "DataDef.h"

#ifdef __cplusplus
extern "C"{
#endif

/*!
 * @brief
 * param[in] message
 * return
 */
bool parseSmartPlugStatusJsonForC(const char* jsonString, SmartPlugInfo* info);

#ifdef __cplusplus
}
#endif
#endif