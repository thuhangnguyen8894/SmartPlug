/*****************************************************************************/
/*!
 * @file JsonBuilder.h
 * @brief The declaration of JsonBuilder.
 *
 * Copyright (c) Tien Nguyen Anh
 *
 * @detail The JsonBuilder can convert a array format message to JSON format.
 *             It's duty is convert a message of Arduino to JSON.
 *
 * Modified History
 * ---------------
 * 2016-Dec-21 Created tien.nguyenanh94@gmail.com
 */
/*****************************************************************************/

#ifndef __JSON_BUILDER_H__
#define __JSON_BUILDER_H__

#include "JsonCommon.h"

/*!
 * @brief
 * param[in] message
 * return
 */
bool buildJson(const char* message, char** jsonString);

/*!
 * @brief
 * param[in] pTree
 * param[out] jsonString
 * return
 */
std::string writeJsonToString(boost::property_tree::ptree& pTree);

#endif
