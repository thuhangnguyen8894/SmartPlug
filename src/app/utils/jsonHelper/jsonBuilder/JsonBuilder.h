/*****************************************************************************/
/*!
 * @file JsonBuilder.h
 * @brief The declaration of JsonBuilder.
 *
 * Copyright (c) 2017 Tien Anh Nguyen
 *
 * @detail The JsonBuilder can convert a array format message to JSON format.
 *             It's duty is convert a message of Arduino to JSON.
 *
 * Modified History
 * ---------------
 * 2017-Jan-05 Created tien.nguyenanh94@gmail.com
 * 2017-Jan-11 Modified tn-trang.tran@outlook.com
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
bool buildJson(const std::string& message, std::string& jsonString);

/*!
 * @brief
 * param[in] pTree
 * param[out] jsonString
 * return
 */

#endif
