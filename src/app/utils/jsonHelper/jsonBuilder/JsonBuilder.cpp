/*****************************************************************************/
/*!
 * @file JsonBuilder.cpp
 * @brief The implementation of JsonBuilder.
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
/*****************************************************************************/

#include <iostream>
#include <regex>
#include <string>

#include "JsonBuilder.h"

#ifdef UNITTEST
#define STATIC
#else
#define STATIC static
#endif

/*!
 * @internal
 */
STATIC bool buildJsonMessageType(const MESSAGE_TYPE& messageType,
                                boost::property_tree::ptree& messageTypeTree)
{
    if (messageType == MESSAGE_TYPE_DEFAULT)
    {
        return false;
    }

    messageTypeTree.put(ATTR_JSON_MESSAGE_TYPE, MESSAGE_TYPE_SMART_PLUG_STATUS_STR);

    return true;
}

/*!
 * @internal
 */
STATIC bool buildSmartPlugStatusJson(const char* message,
                                    boost::property_tree::ptree& dataTree)
{
    if (getJSONMessageType(message) == MESSAGE_TYPE_DEFAULT)
    {
        return false; //
    }

    if (strcmp(message + 1, ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_OFF) == 0)
    {
        dataTree.put(ATTR_JSON_SMART_PLUG_STATUS, 
                                    ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_OFF);    
    }

    if (strcmp(message + 1, ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_ON) == 0)
    {
        dataTree.put(ATTR_JSON_SMART_PLUG_STATUS, 
                                    ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_ON);    
    }
    
    return true;
}

/*!
 * @internal
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
 * @internal
 */
STATIC bool buildIPSenderJSON(const char* ipAddress,
                                boost::property_tree::ptree& senderTree)
{
    boost::property_tree::ptree senderDataTree;

    std::vector<std::string> token = splitWordRegex(std::string(ipAddress),
                                    std::string(IP_PORT_REGEX_SPLITTER));

    if (token.size() != IP_PORT_TOKEN_SIZE)
    {
        return false;
    }

    senderTree.put(ATTR_JSON_IP, token[0]);
    senderTree.put(ATTR_JSON_PORT, token[1]);

    return true;
}

/*!
 * @internal
 */
std::string writeJsonToString(boost::property_tree::ptree& pTree)
{
    std::ostringstream buffer; 
    boost::property_tree::write_json(buffer, pTree, false); 
    
    return buffer.str();
}

/*!
 * @internal Using Regex to break message down into two part:
 *                 Data and IP of sender
 */
bool buildJson(const char* message, char** jsonString)
{
    boost::property_tree::ptree root;
    boost::property_tree::ptree messageTypeTree;
    boost::property_tree::ptree dataTree;
    boost::property_tree::ptree senderTree;

    std::vector<std::string> token = splitWordRegex(std::string(message),
                                    std::string(SENSOR_MESSAGE_SPLITTER));

    MESSAGE_TYPE messageType = getJSONMessageType(token[0].c_str());

    if (!buildJsonMessageType(messageType, root))
    {
        return false;
    }

    if (!buildSmartPlugStatusJson(token[0].c_str(), dataTree))
    {
        return false;
    }

    if (!buildIPSenderJSON(token[1].c_str(), senderTree))
    {
        return false;
    }

    root.add_child(ATTR_JSON_DATA, dataTree);
    root.add_child(ATTR_JSON_SENDER, senderTree);

    *jsonString = strdup(writeJsonToString(root).c_str());

    return true;
}
