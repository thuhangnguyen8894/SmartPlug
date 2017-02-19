/*****************************************************************************/
/*!
 * @file JsonCommon.cpp
 * @brief The implementation of JsonCommon.h
 *
 * Copyright (c) 2017 Tien Anh Nguyen
 *
 * @detail
 *
 * Modified History
 * ---------------
 * 2017-Jan-03 Created tien.nguyenanh94@gmail.com
 * 2017-Jan-07 Modified tn-trang.tran@outlook.com
 * 2017-Jan-11 Modified tn-trang.tran@outlook.com
 * 2017-Jan-18 Modified tn-trang.tran@outlook.com
 */
/*****************************************************************************/

#include "JsonCommon.h"

/*!
 * Test message from Arduino.
 * Template: "PlugStatus;IPAddress:Port"
 */
bool isSensorMessage(const std::string& message)
{
    std::string messageStr(message);

    if (messageStr.length() > MAX_SENSOR_MESSAGE_LENGTH
        || messageStr.length() <= 0)
    {
        return false;
    }

    if (messageStr.find(SENSOR_MESSAGE_SPLITTER) == std::string::npos)
    {
        return false;
    }

    if (messageStr.find(IP_PORT_REGEX_SPLITTER) == std::string::npos)
    {
        return false;
    }

    if (messageStr.find(DATE_TIME_SLASH) == std::string::npos)
    {
        return false;
    }

    if (messageStr.find(DATE_TIME_SPACE) == std::string::npos)
    {
        return false;
    }

    return true;
}

/*!
 * Test JSON Message Type.
 * SMART_PLUG_MESSAGE_VALUE is "P".
 * "P" define feature Plug send JSON message.
 */
MESSAGE_TYPE getJSONMessageType(const std::string& message)
{
    switch(message[0])  
    {
    case SMART_PLUG_MESSAGE_VALUE:
        return MESSAGE_TYPE_SMART_PLUG_STATUS;
    default:
        return MESSAGE_TYPE_DEFAULT;
    }
}

/*!
 * Convert message type into explicit string
 */
std::string convertMessageTypeToStr(const MESSAGE_TYPE& messageType)
{
    switch(messageType)
    {
    case MESSAGE_TYPE_SMART_PLUG_STATUS:
        return std::string(MESSAGE_TYPE_SMART_PLUG_STATUS_STR);
    default:
        return std::string("MESSAGE_TYPE_DEFAULT");
    }
}

/*!
 * Convert JSON to Ptree
 */
bool convertJsonStrToPtree(const std::string& jsonString,
                                    boost::property_tree::ptree& dataTree)
{
    std::istringstream buffer(jsonString);
    boost::property_tree::read_json(buffer, dataTree);

    return true;
}