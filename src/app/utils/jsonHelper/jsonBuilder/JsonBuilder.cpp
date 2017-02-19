/*****************************************************************************/
/*!
 * @file JsonBuilder.cpp
 * @brief The implementation of JsonBuilder.
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
 * 2017-Feb-11 Modified tn-trang.tran@outlook.com
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
 * Build message type into name and value of JSON
 */
STATIC bool buildJsonMessageType(const MESSAGE_TYPE& messageType,
                                boost::property_tree::ptree& messageTypeTree)
{
    if (messageType == MESSAGE_TYPE_DEFAULT)
    {
        return false;
    }

    messageTypeTree.put(ATTR_JSON_MESSAGE_TYPE, ATTR_JSON_SMART_PLUG_STATUS_VALUE);

    return true;
}

/*!
 * @internal
 * Split the message with criterion
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
 * Build status of Smart Plug into name and value of JSON
 */
STATIC bool buildSmartPlugStatusJson(const std::string& message, const std::string& ip_port_jack, 
                                    boost::property_tree::ptree& dataTree)
{
    /*!
     * 
     */
    if (getJSONMessageType(message) == MESSAGE_TYPE_DEFAULT)
    {
        return false;
    }

    /*!
     * 
     */
    std::vector<std::string> status = splitWordRegex(message,
                                    std::string(IP_PORT_REGEX_SPLITTER));
    if (status.size() != JSON_DATA_SIZE)
    {
        return false;
    }

    std::string strStatusUseElectric = status[0].c_str();
    std::string strStatusElectric = status[1].c_str();
    std::string strJackRelay = status[2].c_str();

    /*!
     *
     */
    if (strStatusUseElectric.compare(ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_P_ON) == 0)
    {
        dataTree.put(ATTR_JSON_SMART_PLUG_STATUS_VALUE, 
                                    ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_ON);
    }

    if (strStatusUseElectric.compare(ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_P_OFF) == 0)
    {
        dataTree.put(ATTR_JSON_SMART_PLUG_STATUS_VALUE, 
                                    ATTR_JSON_SMART_PLUG_MESSAGE_VALUE_OFF);  
    }

    /*!
     * 
     */
    if (strStatusElectric.compare(ATTR_JSON_ELECTRIC_MESSAGE_VALUE_ACTIVE) == 0)
    {
        dataTree.put(ATTR_JSON_ELECTRIC_STATUS_VALUE,
                                    ATTR_JSON_ELECTRIC_MESSAGE_VALUE_ACTIVE);
    }

    if (strStatusElectric.compare(ATTR_JSON_ELECTRIC_MESSAGE_VALUE_UNACTIVE) == 0)
    {
        dataTree.put(ATTR_JSON_ELECTRIC_STATUS_VALUE,
                                   ATTR_JSON_ELECTRIC_MESSAGE_VALUE_UNACTIVE);
    }
    /*!
     * 
     */
    if (strJackRelay.compare(ATTR_JSON_JACK_RELAY_VALUE_9) == 0)
    {
        dataTree.put(ATTR_JSON_JACK_RELAY_VALUE,
                                   ATTR_JSON_JACK_RELAY_VALUE_9);
    }

    if (strJackRelay.compare(ATTR_JSON_JACK_RELAY_VALUE_8) == 0)
    {
        dataTree.put(ATTR_JSON_JACK_RELAY_VALUE,
                                   ATTR_JSON_JACK_RELAY_VALUE_8);
    }

    if (strJackRelay.compare(ATTR_JSON_JACK_RELAY_VALUE_7) == 0)
    {
        dataTree.put(ATTR_JSON_JACK_RELAY_VALUE,
                                   ATTR_JSON_JACK_RELAY_VALUE_7);
    }

    if (strJackRelay.compare(ATTR_JSON_JACK_RELAY_VALUE_6) == 0)
    {
        dataTree.put(ATTR_JSON_JACK_RELAY_VALUE,
                                   ATTR_JSON_JACK_RELAY_VALUE_6);
    }

    if (strJackRelay.compare(ATTR_JSON_JACK_RELAY_VALUE_5) == 0)
    {
        dataTree.put(ATTR_JSON_JACK_RELAY_VALUE,
                                   ATTR_JSON_JACK_RELAY_VALUE_5);
    }

    if (strJackRelay.compare(ATTR_JSON_JACK_RELAY_VALUE_4) == 0)
    {
        dataTree.put(ATTR_JSON_JACK_RELAY_VALUE,
                                   ATTR_JSON_JACK_RELAY_VALUE_4);
    }

    dataTree.put(ATTR_JSON_IP_PORT_JACK_VALUE, ip_port_jack);

    return true;
}

/*!
 * @internal 
 * Build IP and Port of Arduino into name and value of JSON
 */
STATIC bool buildIPSenderJSON(const std::string& ipAddress,
                                boost::property_tree::ptree& senderTree)
{
    boost::property_tree::ptree senderDataTree;

    std::vector<std::string> token = splitWordRegex(ipAddress,
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
 * Build Datetime into JSON
 * DON'T COMPLEX
 */
STATIC bool buildIDJSON(const std::string& message,
                                boost::property_tree::ptree& idTree)
{
    boost::property_tree::ptree idDataTree;

    idTree.put(ATTR_JSON_ID_TABLE_TIMER, message);
    return true;
}

/*!
 * @internal 
 * Build Datetime into JSON
 * DON'T COMPLEX
 */
STATIC bool buildDatetimeJSON(const std::string& message,
                                boost::property_tree::ptree& dateTimeTree)
{
    boost::property_tree::ptree dateTimeDataTree;

    /* splites strDateTime by DATE_TIME_SPACE
     * DATE_TIME_SPACE mean "  "
     */
    std::vector<std::string> dateTime = splitWordRegex(message,
                                    std::string(DATE_TIME_SPACE));

    if (dateTime.size() != DATE_TIME_TOKEN_SIZE)
    {
        return false;
    }
    
    //strDate = 1/18/2017
    std::string strDate = dateTime[0].c_str();

    //strTime = 21:18:21
    std::string strTime = dateTime[1].c_str();

    /* splites strDate by DATE_TIME_SLASH
     * DATE_TIME_SLASH mean "/"
     */
    std::vector<std::string> date = splitWordRegex(strDate,
                                    std::string(DATE_TIME_SLASH));
    
    /* put day, month and year of JSON string to dateTimeTree
     * date[0] = 1
     * date[1] = 18
     * date[2] = 2017
     */
    dateTimeTree.put(ATTR_JSON_MONTH, date[0]);
    dateTimeTree.put(ATTR_JSON_DAY, date[1]);
    dateTimeTree.put(ATTR_JSON_YEAR, date[2]);

    /* splites strTime by IP_PORT_REGEX_SPLITTER
     * IP_PORT_REGEX_SPLITTER mean ":"
     */
    std::vector<std::string> time = splitWordRegex(strTime,
                                    std::string(IP_PORT_REGEX_SPLITTER));

    /* put hour, minutes and second of JSON string to dateTimeTree
     * time[0] = 21
     * time[1] = 18
     * time[2] = 21
     */
    dateTimeTree.put(ATTR_JSON_HOUR, time[0]);
    dateTimeTree.put(ATTR_JSON_MINUTES, time[1]);
    dateTimeTree.put(ATTR_JSON_SECOND, time[2]);

    return true;
}

/*!
 * @internal
 * split_IP_PORT
 */
 std::string split_IP_PORT(const std::string& message)
 {
    return message;
 }

/*!
 * @internal
 * split_JACK
 */
std::string split_JACK(const std::string& message)
{
    std::vector<std::string> status = splitWordRegex(message,
                                    std::string(IP_PORT_REGEX_SPLITTER));
    std::string jack = status[2].c_str();

    if (jack.compare(ATTR_JSON_JACK_RELAY_VALUE_9) == 0)
    {
        return ATTR_JSON_JACK_RELAY_VALUE_9;
    }

    if (jack.compare(ATTR_JSON_JACK_RELAY_VALUE_8) == 0)
    {
        return ATTR_JSON_JACK_RELAY_VALUE_8;
    }

    if (jack.compare(ATTR_JSON_JACK_RELAY_VALUE_7) == 0)
    {
        return ATTR_JSON_JACK_RELAY_VALUE_7;
    }

    if (jack.compare(ATTR_JSON_JACK_RELAY_VALUE_6) == 0)
    {
        return ATTR_JSON_JACK_RELAY_VALUE_6;
    }

    if (jack.compare(ATTR_JSON_JACK_RELAY_VALUE_5) == 0)
    {
        return ATTR_JSON_JACK_RELAY_VALUE_5;
    }

    if (jack.compare(ATTR_JSON_JACK_RELAY_VALUE_4) == 0)
    {
        return ATTR_JSON_JACK_RELAY_VALUE_4;
    }
}

/*!
 * @internal
 * Write JSON
 */
std::string writeJsonToString(boost::property_tree::ptree& pTree)
{
    std::ostringstream buffer; 
    boost::property_tree::write_json(buffer, pTree, false); 
    
    return buffer.str();
}


/*!
 * @internal 
 * Using Regex to break message down into two part:
 * Data and IP of sender
 */
bool buildJson(const std::string& message, std::string& jsonString)
{
    boost::property_tree::ptree root;
    boost::property_tree::ptree messageTypeTree;
    boost::property_tree::ptree dataTree;
    boost::property_tree::ptree senderTree;
    boost::property_tree::ptree idTree;
    boost::property_tree::ptree dateTimeTree;

    std::vector<std::string> token = splitWordRegex(message,
                                    std::string(SENSOR_MESSAGE_SPLITTER));
    if (token.size() < JSON_TOKEN_SIZE)
    {
        return false;
    }

    MESSAGE_TYPE messageType = getJSONMessageType(token[0].c_str());

    if (!buildJsonMessageType(messageType, root))
    {
        return false;
    }

    /*
     * Handle string ip_port_jack
     */
    std::string ip_port = split_IP_PORT(token[1].c_str());
    std::string jack = split_JACK(token[0].c_str());
    std::string ip_port_jack = ip_port + ":" + jack;
    

    if (!buildSmartPlugStatusJson(token[0].c_str(), ip_port_jack.c_str(), dataTree))
    {
        return false;
    }

    if (!buildIPSenderJSON(token[1].c_str(), senderTree))
    {
        return false;
    }

    if (!buildIDJSON(token[2].c_str(), idTree))
    {
        return false;
    }

    if (!buildDatetimeJSON(token[3].c_str(), dateTimeTree))
    {
        return false;
    }

    root.add_child(ATTR_JSON_DATA, dataTree);
    root.add_child(ATTR_JSON_ID, idTree);
    root.add_child(ATTR_JSON_MOMENT, dateTimeTree);
    root.add_child(ATTR_JSON_SENDER, senderTree);

    jsonString = writeJsonToString(root);

    return true;
}