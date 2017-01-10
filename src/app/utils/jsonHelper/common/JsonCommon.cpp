/*****************************************************************************/
/*!
 * @file JsonCommon.cpp
 * @brief The implementation of JsonCommon.h
 *
 * Copyright (c) Trang Tran 2017
 *
 * @detail
 *
 * Modified History
 * ---------------
 * 2017-Jan-05 Created tn-trang.tran@outlook.com
 * 2016-Dec-22 Modified tn-trang.tran@outlook.com
 */
/*****************************************************************************/

#include "JsonCommon.h"

/*!
 * @internal
 */
bool isSensorMessage(const std::string& message)
{
    std::string messageStr(message);

    if (messageStr.length() > MAX_SENSOR_MESSAGE_LENGTH
        || messageStr.length() <= 0)
    {
        return false;
    }

    return true;
}

MESSAGE_TYPE getJSONMessageType(const std::string& message)
{
    switch(message[0]) 
    {
    case SMART_PLUG_MESSAGE_TYPE:
        return MESSAGE_TYPE_SMART_PLUG_STATUS;
    case SMART_PLUG_MESSAGE_VALUE_ON:
        return MESSAGE_TYPE_SMART_PLUG_STATUS;
    case SMART_PLUG_MESSAGE_VALUE_OFF:
        return MESSAGE_TYPE_SMART_PLUG_STATUS;
    default:
        return MESSAGE_TYPE_DEFAULT;
    }
}

/*!
 * @internal
 */
std::string convertMessageTypeToStr(const MESSAGE_TYPE& messageType)
{
    switch(messageType)
    {
    case MESSAGE_TYPE_SMART_PLUG_STATUS:
        return std::string(MESSAGE_TYPE_SMART_PLUG_STATUS_STR);
    case MESSAGE_TYPE_CONTROL_SMART_PLUG:
        return std::string(MESSAGE_TYPE_CONTROL_SMART_PLUG_STR);
    default:
        return std::string("MESSAGE_TYPE_DEFAULT");
    }
}

bool convertJsonStrToPtree(const std::string& jsonString,
                                    boost::property_tree::ptree& dataTree)
{
    std::istringstream buffer(jsonString);
    boost::property_tree::read_json(buffer, dataTree);

    return true;
}