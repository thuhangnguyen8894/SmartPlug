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

#include <iostream>
#include <regex>
#include <string>
#include "JsonCommon_smart_device_status_value.h"

/*!
 * Test message from Arduino.
 */
bool isSensorMessage(const std::string& message)
{
    std::string messageStr(message);

    if (messageStr.length() > MAX_SMART_DEVICE_STATUS_VALUE
        || messageStr.length() <= 0)
    {
        return false;
    }

    if (messageStr.find(SEMICOLON_SPLITTER) == std::string::npos)
    {
        return false;
    }

    if (messageStr.find(COLON_SPLITTER) == std::string::npos)
    {
        return false;
    }

    if (messageStr.find(SLASH_SPLITTER) == std::string::npos)
    {
        return false;
    }

    if (messageStr.find(UNDERSCORS_SPLITTER) == std::string::npos)
    {
        return false;
    }

    return true;
}

/*!
 * Function split message to critial something.
 */
std::vector<std::string> splitWordRegex(const std::string& message,
                            const std::string& splitter)
{
    std::regex rgxSplitter(splitter);
    std::vector<std::string> token;
    std::sregex_token_iterator iter(message.begin(),
                                    message.end(),
                                    rgxSplitter,
                                    -1);

    std::sregex_token_iterator end;
    for(; iter != end; iter++)
    {
        token.push_back(*iter);
    }

    return token;
}

/*!
 * Test JSON Message Type.
 * Each feature has special Message Type
 */
MESSAGE_TYPE getJSONMessageType(const std::string& message)
{
    if (strMessageType == MESSAGE_TYPE_SMART_DEVICE_STATUS_VALUE)  
    {
        return MESSAGE_TYPE_SMART_DEVICE_STATUS;
    }
    if (strMessageType == MESSAGE_TYPE_DEFAULT_VALUE)
    {
        return MESSAGE_TYPE_DEFAULT;
    }
}

/*!
 * Convert message type into explicit string
 */
std::string convertMessageTypeToStr(const MESSAGE_TYPE& messageType)
{
    if (messageType == MESSAGE_TYPE_SMART_DEVICE_STATUS)
    {
        return std::string(MESSAGE_TYPE_SMART_DEVICE_STATUS_VALUE);
    }
    else
    {
        return std::string(MESSAGE_TYPE_DEFAULT_VALUE);
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