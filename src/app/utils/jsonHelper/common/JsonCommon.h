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

#define MAX_SENSOR_MESSAGE_LENGTH 5
#define IP_PORT_TOKEN_SIZE 2

#define SMART_PLUG_MESSAGE_TYPE 'S'

#define SMART_PLUG_MESSAGE_VALUE_ON 'N'
#define SMART_PLUG_MESSAGE_VALUE_OFF 'F'
#define ATTR_JSON_SMART_PLUG_STATUS "SMART_PLUG_STATUS"

#define ATTR_JSON_MESSAGE_TYPE "MESSAGE_TYPE"
#define ATTR_JSON_DATA "data"
#define ATTR_JSON_SMART_PLUG_STATUS "SMART_PLUG_STATUS"
#define ATTR_JSON_MOMENT "moment"
#define LIGHT_INTENSITY_TOPIC "SMART_PLUG_STATUS"
#define CONTROL_SMART_PLUG_TOPIC "LIGHT_CONTROL_SMART_PLUG_TOPIC"

#define ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_OFF "OFF"
#define ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_ON "ON"
#define MESSAGE_TYPE_SMART_PLUG_STATUS_STR "SMART_PLUG_STATUS"
#define MESSAGE_TYPE_CONTROL_SMART_PLUG_STR "CONTROL_SMART_PLUG"

enum MESSAGE_TYPE
{
    MESSAGE_TYPE_DEFAULT = -1,
    MESSAGE_TYPE_SMART_PLUG_STATUS,
    MESSAGE_TYPE_CONTROL_SMART_PLUG
};

/*!
 * @brief
 * param[in] message
 * return
 */
MESSAGE_TYPE getJSONMessageType(const char* message);

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
bool isSensorMessage(const char* message);


/*!
 * @brief
 * param[in] message
 * return
 */
bool convertJsonStrToPtree(const char* jsonString,
                                    boost::property_tree::ptree& dataTree);

#endif
