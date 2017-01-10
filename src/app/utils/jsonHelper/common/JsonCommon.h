/***************************************************************************/
/*!
 * @file JsonCommon.h
 * @brief The declaration which is used in JsonBuilder and JsonParser
 *
 * Copyright (c) Trang Tran 2017
 *
 * @detail
 *
 * Modified History
 * ---------------
 * 2017-Jan-05 Created tn-trang.tran@outlook.com
 * 2017-Jan-07 Modified tn-trang.tran@outlook.com
 */
/***************************************************************************/

#ifndef __COMMON_H__
#define __COMMON_H__

#include <iostream>
#include <string.h>
#include <string>
#include <stdint.h>
#include <math.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <DataDef.h>

/*!
 * @brief
 * param[in] message
 * return
 */
MESSAGE_TYPE getJSONMessageType(const std::string& message);

/*!
 * @brief
 * param[in] message
 * return
 */
std::string convertMessageTypeToStr(const MESSAGE_TYPE& messageType);

/*!
 * @brief
 * param[in] message
 * return
 */
bool isSensorMessage(const std::string& message);


/*!
 * @brief
 * param[in] message
 * return
 */
bool convertJsonStrToPtree(const std::string& jsonString,
                                    boost::property_tree::ptree& dataTree);

#endif
