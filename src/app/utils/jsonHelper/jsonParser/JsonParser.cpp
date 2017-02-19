/*****************************************************************************/
/*!
 * @file JsonParser.cpp
 * @brief
 *
 * Copyright (c) Tien Nguyen Anh
 *
 * @detail 
 *
 * Modified History
 * ---------------
 * 2017-Jan-05 Created tien.nguyenanh94@gmail.com
 * 2017-Jan-07 Modified tn-trang.tran@outlook.com
 * 2017-Jan-11 Modified tn-trang.tran@outlook.com
 * 2017-Jan-18 Modified tn-trang.tran@outlook.com
 * 2017-Feb-11 Modified tn-trang.tran@outlook.com
 */
/*****************************************************************************/

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "JsonParser.h"

#ifdef UNITTEST
#define STATIC
#else
#define STATIC static
#endif

/*!
 * @internal
 */
STATIC std::string getJsonPath(const std::string& source,
                                            const std::string& destination)
{
    std::string jsonPath;
    jsonPath.append(source);
    jsonPath.append(JSON_PATH_SPLITTER);
    jsonPath.append(destination);

    return jsonPath;
}

/*!
 * @internal
 */
bool parseSmartPlugStatusJson(const std::string& jsonString,
                                                SmartDeviceInfo& info)
{
    boost::property_tree::ptree pTree;
    
    if (jsonString.compare("") == 0)
    {
        return false;
    }

    if (!convertJsonStrToPtree(jsonString, pTree))
    {
        return false;
    }

    /*!
     * Parse Information of Sender
     */
    /**!
     ** Parse Information of IP Address
     **/
    std::string jsonIPPath = getJsonPath(ATTR_JSON_SENDER, ATTR_JSON_IP);
    std::string ipStr = pTree.get<std::string>(jsonIPPath);

    /**!
     ** Parse Information of Port
     **/
    std::string jsonPortPath = getJsonPath(ATTR_JSON_SENDER, ATTR_JSON_PORT);
    std::string portStr = pTree.get<std::string>(jsonPortPath);

    /**!
     ** Parse Information of Status Use Electric of Device
     **/
    std::string jsonSmartPlugStatusUseElectricPath = getJsonPath(ATTR_JSON_DATA,
                                                ATTR_JSON_SMART_PLUG_STATUS_VALUE);
    std::string smartPlugStatusUseElectricStr = 
                        pTree.get<std::string>(jsonSmartPlugStatusUseElectricPath);

    /**!
     ** Parse Information of Status of Electric
     **/
    std::string jsonSmartPlugStatusElectricPath = getJsonPath(ATTR_JSON_DATA,
                                                ATTR_JSON_ELECTRIC_STATUS_VALUE);
    std::string smartPlugStatusElectricStr = 
                        pTree.get<std::string>(jsonSmartPlugStatusElectricPath);

    /**!
     ** Parse Information of Jack power of Relay
     **/
    std::string jsonJackRelayPath = getJsonPath(ATTR_JSON_DATA,
                                                ATTR_JSON_JACK_RELAY_VALUE);
    std::string jackRelayStr = pTree.get<std::string>(jsonJackRelayPath);

    /**!
     ** Parse Information of ip, port and jack of Device
     **/
    std::string ipPortJackPath = getJsonPath(ATTR_JSON_DATA, 
                                                ATTR_JSON_IP_PORT_JACK_VALUE);
    std::string ipPortJackStr = pTree.get<std::string>(ipPortJackPath);
    /**!
     ** Parse Information of ID of Table Timer
     **/
    std::string jsonIDTableTimerPath = getJsonPath(ATTR_JSON_ID,
                                                ATTR_JSON_ID_TABLE_TIMER);
    std::string idTableTimerStr = pTree.get<std::string>(jsonIDTableTimerPath);

    /**!
     ** Parse Information of Timer of Month
     **/
    std::string jsonDateTimeMonth = getJsonPath(ATTR_JSON_MOMENT, ATTR_JSON_MONTH);
    std::string monthStr = pTree.get<std::string>(jsonDateTimeMonth);

    /**!
     ** Parse Information of Timer of Day
     **/
    std::string jsonDateTimeDay = getJsonPath(ATTR_JSON_MOMENT, ATTR_JSON_DAY);
    std::string dayStr = pTree.get<std::string>(jsonDateTimeDay);

    /**!
     ** Parse Information of Timer of Year
     **/
    std::string jsonDateTimeYear = getJsonPath(ATTR_JSON_MOMENT, ATTR_JSON_YEAR);
    std::string yearStr = pTree.get<std::string>(jsonDateTimeYear);

    /**!
     ** Parse Information of Timer of Hour
     **/
    std::string jsonDateTimeHour = getJsonPath(ATTR_JSON_MOMENT, ATTR_JSON_HOUR);
    std::string hourStr = pTree.get<std::string>(jsonDateTimeHour);

    /**!
     ** Parse Information of Timer of Minutes
     **/
    std::string jsonDateTimeMinutes = getJsonPath(ATTR_JSON_MOMENT, ATTR_JSON_MINUTES);
    std::string minutesStr = pTree.get<std::string>(jsonDateTimeMinutes);

    std::string jsonDateTimeSecond = getJsonPath(ATTR_JSON_MOMENT, ATTR_JSON_SECOND);
    std::string secondStr = pTree.get<std::string>(jsonDateTimeSecond);

    /**!
     ** Put value into Structure
     **/
    strcpy(info.data.status_use_electric, smartPlugStatusUseElectricStr.c_str());
    strcpy(info.data.status_electric, smartPlugStatusElectricStr.c_str());
    strcpy(info.data.jack_relay, jackRelayStr.c_str());
    strcpy(info.data.ip_port_jack, ipPortJackStr.c_str());
    strcpy(info.id.id_timer, idTableTimerStr.c_str());

    info.datetimesp.monthSP = std::stol(monthStr);
    info.datetimesp.daySP = std::stol(dayStr);
    info.datetimesp.yearSP = std::stol(yearStr);
    info.datetimesp.hourSP = std::stol(hourStr);
    info.datetimesp.minSP = std::stol(minutesStr);
    info.datetimesp.secSP = std::stol(secondStr);

    info.sender.port = std::stol(portStr);
    strcpy(info.sender.ip, ipStr.c_str());
}